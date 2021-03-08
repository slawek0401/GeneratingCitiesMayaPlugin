#include "PointBasedAlgorythmGenerator.h"

PointBasedAlgorythmGenerator::PointBasedAlgorythmGenerator(TextureFactory texFactory, unsigned pointNumber, double xMin, double xMax, double zMin, double zMax) : PointBasedAlgorythmGenerator(texFactory, pointNumber){
	limitPoints.push_back(Point(xMin, zMin));
	limitPoints.push_back(Point(xMin, zMax));
	limitPoints.push_back(Point(xMax, zMin));
	limitPoints.push_back(Point(xMax, zMax));
}

PointBasedAlgorythmGenerator::PointBasedAlgorythmGenerator(TextureFactory texFactory, unsigned pointNumber) {
	this->pointNumber = pointNumber;
	this->texFactory = texFactory;
}

void PointBasedAlgorythmGenerator::setCityCenter(Point center) {
	this->cityCenter = center;
	cityCenterSet = true;
}

Point PointBasedAlgorythmGenerator::getCityCenter() {
	return this->cityCenter;
}

void PointBasedAlgorythmGenerator::countCityCenter() {
	Point xMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	Point xMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	Point zMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	auto center = Point((xMax.x - xMin.x) / 2, (xMax.z - xMin.z) / 2);
	this->cityCenter = center;
	cityCenterSet = true;
}

void PointBasedAlgorythmGenerator::setCityDiagonal(double diagonal) {
	this->cityDiagonal = diagonal;
	cityDiagonalSet = true;
}

double PointBasedAlgorythmGenerator::getCityDiagonal() {
	return this->cityDiagonal;
}

void PointBasedAlgorythmGenerator::countCityDiagonal() {
	Point xMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	Point xMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	Point zMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	double cityLength = xMax.x - xMin.x;
	double cityWidth = zMax.z - zMin.z;
	this->cityDiagonal = sqrt(pow2(cityLength) + pow2(cityWidth)) / 2;
	cityDiagonalSet = true;
}

std::vector<double> PointBasedAlgorythmGenerator::findXLimits(double z) {
	Point xMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	Point xMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	std::vector<double> result;
	result.push_back(xMin.x);
	result.push_back(xMax.x);
	return result;
}

void PointBasedAlgorythmGenerator::randomPoints() {
	Point zMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	for (size_t i = 0; i < pointNumber; ++i) {
		double z = randomFactory.getLinearValue(zMin.z, zMax.z);
		auto xLimits = findXLimits(z);
		double x = randomFactory.getLinearValue(xLimits[0], xLimits[1]);
		roadsPoints.push_back(Point(x, z));
	}
}

void PointBasedAlgorythmGenerator::randomMinDistPoints(double minDist, unsigned maxMistakes) {
	Point zMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	unsigned mistakesInRow = 0;
	for (size_t i = 0; i < pointNumber && mistakesInRow < maxMistakes; ++i) {
		double z = randomFactory.getLinearValue(zMin.z, zMax.z);
		auto xLimits = findXLimits(z);
		double x = randomFactory.getLinearValue(xLimits[0], xLimits[1]);
		Point point(x, z);
		bool allPointsOK = true;
		for (auto p : roadsPoints) {
			if (countDistance(point, p) < minDist) {
				allPointsOK = false;
				break;
			}
		}
		if (allPointsOK) {
			roadsPoints.push_back(point);
			mistakesInRow = 0;
		}
		else {
			--i;
			++mistakesInRow;
		}
	}
}

std::vector<Street*> PointBasedAlgorythmGenerator::generate() {
	randomPoints();
	//randomMinDistPoints(4, 20);
	if (!cityCenterSet)
		countCityCenter();
	if (!cityDiagonalSet)
		countCityDiagonal();
	findRoadConnections();
	return streets;
}

void PointBasedAlgorythmGenerator::findRoadConnections(double minLength, double maxLength, double streetWidth) {
	for (auto p : roadsPoints) {
		unsigned roadCount = 0;
		auto indexList = randRange(roadsPoints.size());
		//for (auto q : roadsPoints) {
		for (auto i : indexList) {
			auto q = roadsPoints[i];
			double distance = countDistance(p, q);
			if (distance >= minLength && distance <= maxLength /*&& roadCount < 3*/ && p.z > q.z) {
				streets.push_back(createStreet(p, q, streetWidth));
				roadConnections.push_back(std::make_pair(p, q));
				++roadCount;
			}
		}
	}
}

Street* PointBasedAlgorythmGenerator::createStreet(Point p, Point q, double streetWidth) {
	Point middlePoint(q.x - p.x, q.z - p.z);
	Street* street = new Street(this->getBuildingTypeByDistanceFromCentre(middlePoint), 0.15, -0.5, 0, 1, countDistance(p, q));
	//Street(BuildingType neighbourhood, double walkPathFrac = 0.15, int x1 = 0, int z1 = 0, int width = 2, int length = 2);
	double alfa = atan((q.z - p.z) / (q.x - p.x)) - M_PI / 2;
	double addent = q.x-p.x < 0 ? M_PI : 0;
	//double alfa2 = atan((b->front[0].z - b->front[1].z) / (b->front[0].x - b->front[1].x));
	street->rotateY((alfa + addent) * 180 / M_PI);
	street->move(p.x, p.y, p.z);
	street->assignTexture(texFactory.getRandomTextureByType(TextureType::chodnik), texFactory.getRandomStreetTexture());
	return street;
}

double PointBasedAlgorythmGenerator::countDistance(Point p, Point q) {
	return sqrt(pow2(p.x - q.x) + pow2(p.y - q.y) + pow2(p.z - q.z));
}

double PointBasedAlgorythmGenerator::pow2(double a) {
	return a * a;
}

BuildingType PointBasedAlgorythmGenerator::getBuildingTypeByDistanceFromCentre(Point p) {
	double currentDiagonal = sqrt(pow2(p.x) + pow2(p.z));
	BuildingType types[] = { kamienica, wiezowiec, blok, dom_jednorodzinny };
	double values[] = { 0.2, 0.4, 0.65, 1.0 };
	for (int i = 0; i < 4; ++i)
		if (currentDiagonal / this->cityDiagonal <= values[i])
			return types[i];
	return dom_jednorodzinny;
}