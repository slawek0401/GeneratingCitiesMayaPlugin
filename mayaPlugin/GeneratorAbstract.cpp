#include "GeneratorAbstract.h"

void GeneratorAbstract::setCityCenter(Point center) {
	this->cityCenter = center;
	cityCenterSet = true;
}

Point GeneratorAbstract::getCityCenter() {
	return this->cityCenter;
}

void GeneratorAbstract::countCityCenter() {
	Point xMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	Point xMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	Point zMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	auto center = Point((xMax.x - xMin.x) / 2, (xMax.z - xMin.z) / 2);
	this->cityCenter = center;
	cityCenterSet = true;
}

void GeneratorAbstract::setCityDiagonal(double diagonal) {
	this->cityDiagonal = diagonal;
	cityDiagonalSet = true;
}

double GeneratorAbstract::getCityDiagonal() {
	return this->cityDiagonal;
}

void GeneratorAbstract::countCityDiagonal() {
	Point xMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	Point xMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.x < b.x; });
	Point zMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	double cityLength = xMax.x - xMin.x;
	double cityWidth = zMax.z - zMin.z;
	this->cityDiagonal = sqrt(pow2(cityLength) + pow2(cityWidth)) / 2;
	cityDiagonalSet = true;
}

std::pair<Point, Point> countCrossingPoints(Point start, Point end, double streetWidth) {
	Vector3 vec(start, end);
	vec.setLength(streetWidth / 2);
	Vector3 vec2(vec);
	vec2.setLength(streetWidth);
	Point vecStart = vec2.toPoints(start).second;
	vec.rotateY(-90);
	Point a = vec.toPoints(vecStart).second;
	vec.rotateY(180);
	Point b = vec.toPoints(vecStart).second;
	return std::make_pair(a, b);
}

bool GeneratorAbstract::comparePointAngle(const Point& a, const Point& b, const Point& middle) {
	Vector3 vec1(middle, a);
	Vector3 vec2(middle, b);
	return vec1.angle() > vec2.angle();
}

void GeneratorAbstract::addCrossings() {
	for (auto point : roadsPoints) {
		std::vector<Point> polygonVerts;
		for (auto connection : roadConnections) {
			if (connection.first == point) {
				auto res = countCrossingPoints(connection.first, connection.second, streetWidth);
				polygonVerts.push_back(res.first);
				polygonVerts.push_back(res.second);
			}
			else if (connection.second == point) {
				auto res = countCrossingPoints(connection.second, connection.first, streetWidth);
				polygonVerts.push_back(res.first);
				polygonVerts.push_back(res.second);
			}
		}
		if (polygonVerts.size() > 0) {
			std::sort(polygonVerts.begin(), polygonVerts.end(), [point](Point a, Point b) {return comparePointAngle(a, b, point); });
			Street* crossing = new Polygon(polygonVerts);
			crossing->assignTexture(texFactory.getRandomTextureByType(TextureType::asfalt));
			streets.push_back(crossing);
		}
	}
}

void GeneratorAbstract::addStreets() {
	std::vector<std::vector<double>> streetsBuildings(roadConnections.size(), std::vector<double>(4, 0.0));
	/*for (size_t i = 0; i < roadConnections.size(); ++i) {
		std::vector<double> vec(4, 0);
		for (size_t j = 0; j < 4; ++j)
			vec.push_back(0.0);
		streetsBuildings.push_back(vec);
	}*/
	for (auto point : roadsPoints) {
		std::vector<long long> thisCrossingRoadsIDs;
		std::vector<double> angles;
		for (long long i = 0; i < roadConnections.size(); ++i) {
			auto connection = roadConnections[i];
			if (connection.first == point) {
				thisCrossingRoadsIDs.push_back(i);
				angles.push_back(Vector3(connection.first, connection.second).angle());
			}
			else if (connection.second == point) {
				thisCrossingRoadsIDs.push_back(-i);
				angles.push_back(Vector3(connection.second, connection.first).angle());
			}
		}
		auto anglesSorted(angles);
		std::sort(anglesSorted.begin(), anglesSorted.end());
		std::string DEGUB = "";
		for (auto iter = anglesSorted.begin(); iter != anglesSorted.end(); ++iter) {
			auto iter2 = iter + 1 == anglesSorted.end() ? anglesSorted.begin() : iter + 1;
			size_t index1 = std::find(angles.begin(), angles.end(), *iter) - angles.begin();
			size_t index2 = std::find(angles.begin(), angles.end(), *iter2) - angles.begin();
			auto val = iter + 1 == anglesSorted.end() ? *iter2 + 2 * M_PI : *iter2;
			auto angleDiff = val - *iter;
			double dist = 0.0;
			if (angleDiff < M_PI && angleDiff > 0)
				dist = 2 / tan(angleDiff / 2);
			DEGUB += std::to_string(*iter) + "   ";
			//showDebug(std::to_string(*iter2) + "   " + std::to_string(*iter) + "    "+ std::to_string(angleDiff) + "   " + std::to_string(dist));
			auto i = thisCrossingRoadsIDs[index1];
			if (i > 0)
				streetsBuildings[i][0] = dist;
			else
				streetsBuildings[-i][2] = dist;
			i = thisCrossingRoadsIDs[index2];
			if (i > 0)
				streetsBuildings[i][3] = dist;
			else
				streetsBuildings[-i][1] = dist;
		}
		//showDebug(DEGUB);
	}
	for (auto i = roadConnections.begin(); i != roadConnections.end(); ++i) {
		streets.push_back(createStreet((*i).first, (*i).second, streetsBuildings[i - roadConnections.begin()]));
	}
}

Street* GeneratorAbstract::createStreet(Point p, Point q, std::vector<double> buildingsAlong) {
	Point middlePoint(q.x - p.x, q.z - p.z);
	double streetLength = countDistance(p, q) - 2 * streetWidth;
	Street* street = new Street(this->getBuildingTypeByDistanceFromCentre(middlePoint), 0.15, -streetWidth / 2, streetWidth, streetWidth, streetLength);//w przeciwienstwie do tego ni¿ej tutaj ulica nie zaczyna siê idealnie w punkcie, jest miejsce na skrzyzowanie
	//Street* street = new Street(this->getBuildingTypeByDistanceFromCentre(middlePoint), 0.15, -0.5, 0, 1, countDistance(p, q));
	//Street(BuildingType neighbourhood, double walkPathFrac = 0.15, int x1 = 0, int z1 = 0, int width = 2, int length = 2);
	double alfa = atan((q.z - p.z) / (q.x - p.x)) - M_PI / 2;
	double addent = q.x - p.x < 0 ? M_PI : 0;
	//double alfa2 = atan((b->front[0].z - b->front[1].z) / (b->front[0].x - b->front[1].x));
	street->rotateY((alfa + addent) * 180 / M_PI);
	street->move(p.x, p.y, p.z);
	street->assignTexture(texFactory.getRandomTextureByType(TextureType::chodnik), texFactory.getRandomStreetTexture());
	//showDebug(std::to_string(buildingsAlong[0]) + "   " + std::to_string(buildingsAlong[1]) + "   " + std::to_string(buildingsAlong[2]) + "   " + std::to_string(buildingsAlong[3]));
	if (buildingsAlong[0] + buildingsAlong[1] < streetLength) {
		street->addBuildingAlongRelative(buildingsAlong[0], streetLength - buildingsAlong[1], true);
	}
	if (buildingsAlong[2] + buildingsAlong[3] < streetLength) {
		street->addBuildingAlongRelative(buildingsAlong[2], streetLength - buildingsAlong[3], false);
	}
	return street;
}

BuildingType GeneratorAbstract::getBuildingTypeByDistanceFromCentre(Point p) {
	double currentDiagonal = sqrt(pow2(p.x) + pow2(p.z));
	BuildingType types[] = { kamienica, wiezowiec, blok, dom_jednorodzinny };
	double values[] = { 0.2, 0.4, 0.65, 1.0 };
	for (int i = 0; i < 4; ++i)
		if (currentDiagonal / this->cityDiagonal <= values[i])
			return types[i];
	return dom_jednorodzinny;
}

void GeneratorAbstract::setIgnoreVisualObjects(bool ignoreVisualObjects) {
	this->ignoreVisualObjects = ignoreVisualObjects;
}