#include "Algorythms.h"
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
			setRandomRoofAngle(b,50); // prawdopodobienstwo 50 
			b->move(r, 0, 0);
			b->rotateY(i * (360 / n));
			buildings.push_back(b);
		}
		r += 3;
	}
	return buildings;
}

Building* setRandomHeight(Building* building) { // z rozkladem normalnym (Gaussa)
	//static std::random_device r;
	//static std::default_random_engine e1(r());
	////std::normal_distribution<> normal_dist(6,4);
	//std::lognormal_distribution<> dist(0,0.25);
	//double height = dist(e1);
	//MString a("elo ");
	//a += height;
	//MGlobal::displayInfo(a);
	//if (height <= 0)
	//	height = 1;
	static RandomFactory rand;
	building->setNewHeight(rand.getLogNormalValue());// scale(1, height, 1);
	return building;
}

Building* setRandomRoofAngle(Building* building, int percentageProbability) {
	static std::random_device r;
	static std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, 99);
	int val = uniform_dist(e1);
	if (val < percentageProbability) {
		/*MFloatPoint newPoint = building->vert[0];
		newPoint.y *= 1.1;
		building->vert.set(newPoint, 0);
		newPoint = building->vert[1];
		newPoint.y *= 1.1;
		building->vert.set(newPoint, 1);*/
	}
	return building;
}

std::vector<Street*> getStreetSystem() {
	std::vector<Street*> vec;
	auto str = new Street(-1, -5, 2, 4);
	str->rotateY(90);
	vec.push_back(str);
	//auto str1 = new Street(5, 10, 2, 10);
	//vec.push_back(str1);
	return vec;
}

std::vector<Street*> getManhatanStreetSystem() {
	std::vector<Street*> vec;
	int x1 = -30;
	int y1 = -25;
	for (int i = x1; i < 50; i += 8) {
		for (int j = y1; j < 50; j += 12) {
			auto str = new Street(0, 0, 2, 10);
			str->move(i, 0, j);
			str->addBuildingAlongAllStreet();
			vec.push_back(str);

			auto crossing = new Street(0, 0, 2, 2);
			crossing->move(i, 0, j - 2);
			vec.push_back(crossing);
		}
	}
	for (int i = x1+2; i < 50; i += 8) {
		for (int j = y1; j < 50; j += 12) {
			auto str = new Street(0, 0, 2, 6);
			str->rotateY(-90);
			str->move(i, 0, j);
			str->addBuildingAlongRelative(2, 4, true);
			str->addBuildingAlongRelative(2, 4, false);
			vec.push_back(str);
		}
	}
	return vec;
}

bool isBetween(MFloatPoint a, MFloatPoint x1, MFloatPoint x2) {
	return ((a.x >= x1.x - 0.02 && a.x <= x2.x + 0.02) || (a.x <= x1.x + 0.02 && a.x >= x2.x - 0.02)) &&
		((a.y >= x1.y - 0.02 && a.y <= x2.y + 0.02) || (a.y <= x1.y + 0.02 && a.y >= x2.y - 0.02)) &&
		((a.z >= x1.z - 0.02 && a.z <= x2.z + 0.02) || (a.z <= x1.z + 0.02 && a.z >= x2.z - 0.02));
}

void show(double x, double z) {
	MString a(" ");
	a += x;
	a += "   ";
	a += z;
	MGlobal::displayInfo(a);
}

bool turningNeeded(MFloatPoint x, MFloatPoint y, MFloatPoint v, MFloatPoint w) {
	bool b1 = (x.x > y.x && v.x > w.x) || (x.x < y.x && v.x < w.x);
	if (b1)
		return false;
	return !((x.z > y.z && v.z > w.z) || (x.z < y.z && v.z < w.z));

}

std::vector<Building*> getBuildingsAlongStreets(std::vector<Street*> streets) {
	std::vector<Building*> vec;
	for (Street* street : streets) {
		for (int i = 0; i < street->getBuildingsAlong().size() / 2; i += 2) {
			MFloatPoint v1 = street->getVert()[i];
			MFloatPoint v2 = street->getVert()[i+1];
			getBuildingsAlongOneSideOfStreet(vec, v1, v2);

			/*v1 = street->getVert()[2];
			v2 = street->getVert()[3];
			getBuildingsAlongOneSideOfStreet(vec, v1, v2);*/
		}
	}
	return vec;
}

void getBuildingsAlongOneSideOfStreet(std::vector<Building*> &vec, MFloatPoint v1, MFloatPoint v2) {
	MFloatPoint curr = v1;
	bool nextBuildingNeeded = true;
	while (nextBuildingNeeded) {
		Building* b = new Building();
		b->setAsCuboid();
		setRandomHeight(b);
		double alfa1 = atan((v1.z - v2.z) / (v1.x - v2.x));
		double alfa2 = atan((b->front[0].z - b->front[1].z) / (b->front[0].x - b->front[1].x));
		b->rotateY((alfa1 - alfa2) * 180 / M_PI);
		if (turningNeeded(v1, v2, b->front[0], b->front[1]))
			b->rotateY(180);
		b->move(curr.x - b->front[0].x, curr.y - b->front[0].y, curr.z - b->front[0].z);
		if (isBetween(b->front[1], v1, v2) && isBetween(b->front[0], v1, v2)) {
			vec.push_back(b);
			curr = b->front[1];
		}
		else {
			nextBuildingNeeded = false;
			delete b;
		}
	}
}