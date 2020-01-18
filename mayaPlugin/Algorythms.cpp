#include "Algorythms.h"
#include "Pyramid.h"
#include "Cuboid.h"
#include "TriangularPrism.h"
#include <maya/MGlobal.h>

std::vector<Building*> generateManhatanStyle(int n, int m) {
	std::vector<Building*> buildings;
	int width = n * 3 / 2;
	int length = m * 3 / 2;

	for (int j = -width; j < 3 * n - width; j += 3)
		for (int i = -length; i < 3 * m - length; i += 3) {
			Building* b = new Building();
			b->setAsCuboid(j, i);
			buildings.push_back(b);
		}
	return buildings;
}

std::vector<Building*> generateParisStyle(int circles) {
	std::vector<Building*> buildings;
	double r = 4;
	for (int j = 0; j < circles; ++j) {
		int n = 2 * M_PI * r / 3;
		for (int i = 0; i < n; ++i) {
			Building* b = new Building();
			b->setAsCuboid(0,0);
			setRandomHeight(b);
			b->move(r, 0, 0);
			b->rotateY(i * (360 / n));
			buildings.push_back(b);
		}
		r += 3;
	}
	return buildings;
}

Building* setRandomHeight(Building* building) {
	static RandomFactory rand;
	building->setNewHeight(rand.getLogNormalValue());
	return building;
}

Primitive* setRandomHeight(Primitive* prim) {
	static RandomFactory rand;
	prim->setNewScaleHeight(rand.getLogNormalValue());
	return prim;
}

Building* setRandomWidth(Building* building) {
	static RandomFactory rand;
	building->scale(rand.getLogNormalValue(),1,1);
	return building;
}

std::vector<Street*> getStreetSystem() {
	std::vector<Street*> vec;
	auto str = new Street(BuildingType::wiezowiec, -1, -5, 2, 10);
	str->rotateY(90);
	str->addBuildingAlongAllStreet();
	vec.push_back(str);
	//auto str1 = new Street(5, 10, 2, 10);
	//vec.push_back(str1);
	return vec;
}

BuildingType getBuildingTypeByDistanceFromCentre(int cityWidth, int cityLength, int x, int y) {
	static double cityDiagonal = sqrt(cityLength * cityLength + cityWidth * cityWidth)/2;
	double currentDiagonal = sqrt(x * x + y * y);
	BuildingType types[] = {kamienica, wiezowiec, blok, dom_jednorodzinny};
	double values[] = { 0.2, 0.4, 0.65, 1.0 };
	for (int i = 0; i < 4; ++i) 
		if (currentDiagonal / cityDiagonal <= values[i])
			return types[i];
	return dom_jednorodzinny;
}

void addParkPoints(std::vector<std::vector<int>> &parkPoints, int x, int y, int vertStreetLength, int vertStreetWidth, int horStreetLength, int horStreetWidth) {
	std::vector<int> first{ x + vertStreetWidth, y };
	std::vector<int> second{ x + horStreetLength + vertStreetWidth , y }; 
	std::vector<int> third{ x + vertStreetWidth, y + horStreetWidth + vertStreetLength};
	parkPoints.push_back(first);
	parkPoints.push_back(second);
	parkPoints.push_back(third);
}

bool vertHasParkOnRight(std::vector<std::vector<int>> &parkPoints, int x, int y) {
	for (int i = 1; i < parkPoints.size(); i += 3)
		if (parkPoints[i][0] == x && parkPoints[i][1] == y)
			return true;
	return false;
}

bool horHasParkOnRight(std::vector<std::vector<int>> &parkPoints, int x, int y) {
	for (int i = 0; i < parkPoints.size(); i += 3)
		if (parkPoints[i][0] == x && parkPoints[i][1] == y)
			return true;
	return false;
}

bool horHasParkOnLeft(std::vector<std::vector<int>> &parkPoints, int x, int y) {
	for (int i = 2; i < parkPoints.size(); i += 3)
		if (parkPoints[i][0] == x && parkPoints[i][1] == y)
			return true;
	return false;
}

std::vector<Street*> getManhatanStreetSystem(TextureFactory texFactory, int cityWidth,int cityLength,int vertStreetWidth,int vertStreetLength,int horStreetWidth,int horStreetLength) {
	static RandomFactory rand;
	std::vector<std::vector<int>> parkPoints;
	std::vector<Street*> vec;
	/*int cityWidth = 82;
	int cityLength = 82;
	int vertStreetWidth = 2;
	int vertStreetLength = 10;
	int horStreetWidth = 2;
	int horStreetLength = 6;*/

	int x1 = - cityWidth / 2;
	int y1 = - cityLength / 2;
	for (int i = x1; i < cityWidth / 2; i += horStreetLength + vertStreetWidth) {
		for (int j = y1; j < cityLength / 2; j += vertStreetLength + horStreetWidth) {
			if (j + vertStreetLength < cityLength / 2) {// nie tworz ulicy po ostatnim skrzyzowaniu
				auto str = new Street(getBuildingTypeByDistanceFromCentre(cityWidth, cityLength, i, j), 0.15, 0, 0, vertStreetWidth, vertStreetLength);
				str->move(i, 0, j);
				if (rand.getLinearValue(0,100)<8 && ((i + horStreetLength + vertStreetWidth < cityLength / 2))) {//stworz park
					str->setParkOnLeft();
					str->addBuildingAlongRelative(0, vertStreetLength, true);
					addParkPoints(parkPoints, i, j, vertStreetLength, vertStreetWidth, horStreetLength, horStreetWidth);
				}
				else
					if (vertHasParkOnRight(parkPoints, i, j))
						str->addBuildingAlongRelative(0, vertStreetLength, false);
					else
						str->addBuildingAlongAllStreet();
				str->assignTexture(texFactory.getRandomTextureByType(TextureType::chodnik), texFactory.getRandomStreetTexture());
				vec.push_back(str);
			}
			auto crossing = new Street(BuildingType::undefined, 0, 0, 0, vertStreetWidth, horStreetWidth); // ?moze odwrotnie
			crossing->move(i, 0, j - horStreetWidth);
			crossing->assignTexture(texFactory.getRandomTextureByType(TextureType::chodnik), texFactory.getRandomTextureByType(TextureType::asfalt));
			vec.push_back(crossing);
		}
	}
	for (int i = x1+vertStreetWidth; i < cityWidth / 2; i += horStreetLength + vertStreetWidth) {
		for (int j = y1; j < cityLength / 2; j += vertStreetLength + horStreetWidth) {
			auto str = new Street(getBuildingTypeByDistanceFromCentre(cityWidth, cityLength, i, j), 0.15, 0, 0, horStreetWidth, horStreetLength);
			str->rotateY(-90);
			str->move(i, 0, j);
			if (!horHasParkOnRight(parkPoints, i, j))
				str->addBuildingAlongRelative(vertStreetWidth, horStreetLength - vertStreetWidth, true);
			if (!horHasParkOnLeft(parkPoints, i, j))
				str->addBuildingAlongRelative(vertStreetWidth, horStreetLength - vertStreetWidth, false);
			str->assignTexture(texFactory.getRandomTextureByType(TextureType::chodnik), texFactory.getRandomStreetTexture());
			vec.push_back(str);
		}
	}
	return vec;
}

std::vector<Primitive*> getAdditives(std::vector<Street*> streets, TextureFactory texFactory, int cityWidth, int cityLength, int vertStreetWidth, int vertStreetLength, int horStreetWidth, int horStreetLength) {
	std::vector<Primitive*> res;
	for (auto str : streets) {
		if (str->isParkOnLeft()) {
			int x = str->getVert()[0].x;
			int y = str->getVert()[0].z;
			Primitive* prim = new Plane(x + vertStreetWidth, y, horStreetLength, vertStreetLength);
			prim->assignTexture(texFactory.getRandomTextureByType(TextureType::trawa));
			res.push_back(prim);
		}
	}
	return res;
}

bool isBetween(MFloatPoint a, MFloatPoint x1, MFloatPoint x2) {
	return ((a.x >= x1.x - 0.02 && a.x <= x2.x + 0.02) || (a.x <= x1.x + 0.02 && a.x >= x2.x - 0.02)) &&
		((a.y >= x1.y - 0.02 && a.y <= x2.y + 0.02) || (a.y <= x1.y + 0.02 && a.y >= x2.y - 0.02)) &&
		((a.z >= x1.z - 0.02 && a.z <= x2.z + 0.02) || (a.z <= x1.z + 0.02 && a.z >= x2.z - 0.02));
}

std::vector<Building*> getBuildingsAlongStreets(std::vector<Street*> streets, TextureFactory texFactory) {
	std::vector<Building*> vec;
	for (Street* street : streets) {
		for (int i = 0; i < street->getBuildingsAlong().size(); i += 2) {
			MFloatPoint v1 = street->getBuildingsAlong()[i];
			MFloatPoint v2 = street->getBuildingsAlong()[i+1];
			getBuildingsAlongOneSideOfStreet(vec, v1, v2, texFactory, street->getNeighbourhood());
		}
	}
	return vec;
}

void getBuildingsAlongOneSideOfStreet(std::vector<Building*> &vec, MFloatPoint v1, MFloatPoint v2, TextureFactory texFactory, BuildingType bType) {
	MFloatPoint currentPoint = v1;
	bool nextBuildingNeeded = true;
	while (nextBuildingNeeded) {
		Building* b = BuildingsFactory::createSpecifiedTypeBuilding(bType, texFactory);
		if (countSegmentLength(currentPoint, v2) <= countSegmentLength(b->front[0], b->front[1])) {
			nextBuildingNeeded = false;
			if (countSegmentLength(currentPoint, v2) >= 1) {
				b->scale(1 / countSegmentLength(b->front[0], b->front[1]), 1, 1);
				currentPoint = alignAndAdd(v1, v2, b, vec, currentPoint);
			}
			else {
				delete b;
			}
		}
		else {
			currentPoint = alignAndAdd(v1, v2, b, vec, currentPoint);
		}
	}
}

double countSegmentLength(const MFloatPoint& a1, const MFloatPoint& a2) {
	double x = a1.x - a2.x;
	double y = a1.y - a2.y;
	double z = a1.z - a2.z;
	return sqrt(x * x + y * y + z * z);
}

bool turningNeeded(MFloatPoint x, MFloatPoint y, MFloatPoint v, MFloatPoint w) {
	//return  asin((x.z - y.z) / sqrt(pow(x.z - y.z, 2) + pow(x.x - y.x, 2))) <= 0;
	bool b1 = (x.x > y.x && v.x > w.x) || (x.x < y.x && v.x < w.x);
	if (b1)
		return false;
	return !((x.z > y.z && v.z > w.z) || (x.z < y.z && v.z < w.z));
}

MFloatPoint alignAndAdd(const MFloatPoint& v1, const MFloatPoint& v2, Building* b, std::vector<Building*>& vec, const MFloatPoint& curr) {
	double alfa1 = atan((v1.z - v2.z) / (v1.x - v2.x));
	double alfa2 = atan((b->front[0].z - b->front[1].z) / (b->front[0].x - b->front[1].x));
	b->rotateY((alfa1 - alfa2) * 180 / M_PI);
	if (turningNeeded(v1, v2, b->front[0], b->front[1]))
		b->rotateY(180);
	b->move(curr.x - b->front[0].x, curr.y - b->front[0].y, curr.z - b->front[0].z);
	vec.push_back(b);
	return b->front[1];
}