#include "Algorythms.h"

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
	static std::random_device r;
	static std::default_random_engine e1(r());
	std::normal_distribution<> normal_dist(1,0.5);
	double height = normal_dist(e1);
	building->scale(1, height, 1);
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
	vec.push_back(new Street(3,1,2,10));
}