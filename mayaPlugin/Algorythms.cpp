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
				auto str = new Street(getBuildingTypeByDistanceFromCentre(cityWidth, cityLength, i, j), 0.15, 0, 0, (double)vertStreetWidth, (double)vertStreetLength);
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
		int x = str->getVert()[0].x;
		int y = str->getVert()[0].z;
		if (str->isParkOnLeft()) {
			Primitive* prim = new Plane(x + vertStreetWidth, y, horStreetLength, vertStreetLength);
			prim->assignTexture(texFactory.getRandomTextureByType(TextureType::trawa));
			res.push_back(prim);
		}
		if (str->getBuildingsAlong().size() > 0) {
			addLamp(texFactory, str, res);
			addTrafficLight(texFactory, str, res);
		}
	}
	return res;
}

void addTrafficLight(TextureFactory texFactory, Street* str, std::vector<Primitive*>& res) {
	MFloatPoint v1 = str->getVert()[0];
	MFloatPoint v2 = str->getVert()[1];
	double alfa1 = atan((v1.z - v2.z) / (v1.x - v2.x));
	double alfa2 = atan(-INFINITY);
	double rotation = (alfa1 - alfa2) * 180 / M_PI;
	double x = str->getWalkPathFrac() * str->getWidth();
	double y = str->getLength();
	double x1 = -(1 - str->getWalkPathFrac()) * str->getWidth();
	double y1 = 0;
	Primitive* trafficLight = new TrafficLights(x, y);
	Primitive* trafficLight1 = new TrafficLights(x1, y1);
	trafficLight1->rotateY(180);
	trafficLight->assignTexture(texFactory.getRandomTextureByType(TextureType::metal));
	trafficLight1->assignTexture(texFactory.getRandomTextureByType(TextureType::metal));
	trafficLight->rotateY(rotation);
	trafficLight1->rotateY(rotation);
	if (turningNeeded(v1, v2, MFloatPoint(0, 0, 0), MFloatPoint(0, 0, 1))) {
		trafficLight->rotateY(180);
		trafficLight1->rotateY(180);
	}
	trafficLight->move(v1.x, v1.y, v1.z);
	trafficLight1->move(v1.x, v1.y, v1.z);
	res.push_back(trafficLight);
	res.push_back(trafficLight1);
}

void addLamp(TextureFactory texFactory, Street* str, std::vector<Primitive*>& res) {
	MFloatPoint v1 = str->getVert()[0];
	MFloatPoint v2 = str->getVert()[1];
	double alfa1 = atan((v1.z - v2.z) / (v1.x - v2.x));
	double alfa2 = atan(-INFINITY);
	double rotation = (alfa1 - alfa2) * 180 / M_PI;
	for (int i = 0; i <= str->getLength(); ++i) {
		if (i != str->getLength())
			res.push_back(createLamp(texFactory, str->getWalkPathFrac() * str->getWidth(), i, v1, v2, rotation));
		if (i != 0)
			res.push_back(createLamp(texFactory, (1 - str->getWalkPathFrac()) * str->getWidth(), i, v1, v2, rotation));
	}	
}

Primitive* createLamp(TextureFactory texFactory, double x, double y, MFloatPoint v1, MFloatPoint v2, double rotation) {
	Primitive* lamp = new Lamp(x, y);
	//Primitive* lamp = new TrafficLights(x, y);
	lamp->assignTexture(texFactory.getRandomTextureByType(TextureType::metal));
	lamp->rotateY(rotation);
	if (turningNeeded(v1, v2, MFloatPoint(0, 0, 0), MFloatPoint(0, 0, 1)))
		lamp->rotateY(180);
	lamp->move(v1.x, v1.y, v1.z);
	return lamp;
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
	int i = 0;
	while (nextBuildingNeeded && i < 20) {
		++i;
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

std::vector<unsigned> range(unsigned count) {
	std::vector<unsigned> res;
	for (unsigned i = 0; i < count; ++i)
		res.push_back(i);
	return res;
}

std::vector<unsigned> randRange(unsigned count) {
	static RandomFactory randomFactory;
	return randomFactory.shuffle<unsigned>(range(count));
}

bool intersects(std::pair<Point, Point> a, std::pair<Point, Point> b) {
	Vector3 v(a.first, a.second);
	Vector3 u(b.first, b.second);

	Vector3 v1(a.second, b.first);
	Vector3 v2(a.second, b.second);
	Vector3 v3(b.second, a.first);
	Vector3 v4(b.second, a.second);

	double p1 = vectorProduct(v, v1);
	double p2 = vectorProduct(v, v2);
	double p3 = vectorProduct(u, v3);
	double p4 = vectorProduct(u, v4);

	return  (p1 > 0 && p2 < 0 || p1 < 0 && p2>0) && (p3>0 && p4 < 0 || p3 < 0 && p4>0);
}

double vectorProduct(Vector3 v, Vector3 u) {
	return u.x * v.z - v.x * u.z;
}

void removeDuplicates(std::vector<size_t> &vec) {
	for (auto i = vec.begin() + 1; i != vec.end(); ++i) {
		if (*i == *(i - 1))
			vec.erase(i--);
	}
}

void showDebug(std::string a) {
	MString c(a.data());
	MGlobal::displayInfo(c);
}

double countDistance(Point p, Point q) {
	return sqrt(pow2(p.x - q.x) + pow2(p.y - q.y) + pow2(p.z - q.z));
}

double pow2(double a) {
	return a * a;
}

template <typename T>
long findElement(std::vector<T> vec, T elem) {
	for (long i = 0; i < vec.size(); ++i)
		if (vec[i] == elem)
			return i;
	return -1;
}

template <typename T>
void addAll(std::vector<T>& vec, std::vector<T>& vecToAdd) {
	for (auto elem : vecToAdd)
		vec.push_back(elem);
}