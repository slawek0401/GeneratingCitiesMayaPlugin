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

void PointBasedAlgorythmGenerator::randomFastNoicePoints() {
	FastNoiseLite noise;
	noise.SetFrequency(100);
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	Point zMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	auto xLimits = findXLimits((zMin.z + zMax.z) / 2);
	double area = (zMax.z - zMin.z) * (xLimits[1] - xLimits[0]);
	double step1 = 3;
	double step2 = 3;
	double limit = 0.8 - ((double)pointNumber / area / step1 / step2) * 2;
	for (double z = zMin.z; z < zMax.z; z += step1) {
		auto curXLimits = findXLimits(z);
		for (double x = curXLimits[0]; x < curXLimits[1]; x += step2) {
			double val = noise.GetNoise((float)x, (float)z);
			if (val > limit) {
				roadsPoints.push_back(Point(x, z));
			}
		}
	}
	//showDebug("limit:"+std::to_string(limit) + "   punkty:" + std::to_string(roadsPoints.size()));
}

std::vector<Street*> PointBasedAlgorythmGenerator::generate() {
	showDebug("random points");
	//randomPoints();
	randomMinDistPoints(8, 30);
	//randomFastNoicePoints();
	if (!cityCenterSet)
		countCityCenter();
	if (!cityDiagonalSet)
		countCityDiagonal();
	showDebug("findingConnections");
	findRoadConnections();
	showDebug("deleting intersections");
	deleteRoadsIntersections();
	showDebug("deleting small angle streets");
	deleteSmallAngleRoads();
	if (!ignoreVisualObjects) {
		showDebug("adding streets");
		addStreets();
		showDebug("adding crossings");
		addCrossings();
	}
	return streets;
}

void PointBasedAlgorythmGenerator::deleteRoadsIntersections() {
	bool firstErased = false;
	auto i = roadConnections.begin();
	while(i != roadConnections.end()-1) {
		for (auto j = i+1; j != roadConnections.end(); ++j) {
			if (intersects(*i, *j)) {
				double l1 = Vector3::countSectionLength(*i);
				double l2 = Vector3::countSectionLength(*j);
				// usuwamy krotsza droge
				if (l1 > l2) {
					roadConnections.erase(j--);
				}
				else {
					if (i == roadConnections.begin()) {
						roadConnections.erase(i);
						firstErased = true;
					}
					else
						roadConnections.erase(i--);
					break;
				}
			}
		}
		if (!firstErased) {
			++i;
		}
		else{
			firstErased = false;
			i = roadConnections.begin();
		}
	}
}

void PointBasedAlgorythmGenerator::deleteSmallAngleRoads() {
	for (auto point : roadsPoints) {
		std::vector<size_t> thisCrossingRoadsIDs;
		std::vector<size_t> toDeleteCrossingRoadsIDs;
		std::vector<double> angles;
		for (size_t i = 0; i < roadConnections.size(); ++i) {
			auto connection = roadConnections[i];
			if (connection.first == point) {
				thisCrossingRoadsIDs.push_back(i);
				angles.push_back(Vector3(connection.first, connection.second).angle());
			}
			else if (connection.second == point) {
				thisCrossingRoadsIDs.push_back(i);
				angles.push_back(Vector3(connection.second, connection.first).angle());
			}
		}
		if (angles.size() > 0)
			for (size_t i = 0; i < angles.size()-1; ++i) {
				if (std::find(toDeleteCrossingRoadsIDs.begin(), toDeleteCrossingRoadsIDs.end(), thisCrossingRoadsIDs[i]) != toDeleteCrossingRoadsIDs.end()) // already to delete
					continue;
				for (size_t j = i + 1; j < angles.size(); ++j) {
					if (std::find(toDeleteCrossingRoadsIDs.begin(), toDeleteCrossingRoadsIDs.end(), thisCrossingRoadsIDs[j]) != toDeleteCrossingRoadsIDs.end()) 
						continue;
					if (abs(angles[i] - angles[j]) < M_PI / 6) {
						double l1 = Vector3::countSectionLength(roadConnections[thisCrossingRoadsIDs[i]]);
						double l2 = Vector3::countSectionLength(roadConnections[thisCrossingRoadsIDs[j]]);
						if (l1 > l2)
							toDeleteCrossingRoadsIDs.push_back(thisCrossingRoadsIDs[j]);
						else
							toDeleteCrossingRoadsIDs.push_back(thisCrossingRoadsIDs[i]);
					}
				}
			}
		if (toDeleteCrossingRoadsIDs.size() > 0) {
			std::sort(toDeleteCrossingRoadsIDs.begin(), toDeleteCrossingRoadsIDs.end());
			removeDuplicates(toDeleteCrossingRoadsIDs);
			for (auto i = toDeleteCrossingRoadsIDs.end(); i != toDeleteCrossingRoadsIDs.begin(); --i) {
				auto delID = *(i - 1);
				roadConnections.erase(roadConnections.begin() + delID);
			}
		}
	}
}

void PointBasedAlgorythmGenerator::findRoadConnections(double minLength, double maxLength) {
	for (auto p : roadsPoints) {
		unsigned roadCount = 0;
		auto indexList = randRange(roadsPoints.size());
		//for (auto q : roadsPoints) {
		for (auto i : indexList) {
			auto q = roadsPoints[i];
			double distance = countDistance(p, q);
			if (distance >= minLength && distance <= maxLength /*&& roadCount < 3 */ && p.z > q.z) {
				roadConnections.push_back(std::make_pair(p, q));
				++roadCount;
			}
		}
	}
}