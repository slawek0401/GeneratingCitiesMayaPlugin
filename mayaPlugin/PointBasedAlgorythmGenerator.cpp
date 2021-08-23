#include "PointBasedAlgorythmGenerator.h"



PointBasedAlgorythmGenerator::PointBasedAlgorythmGenerator(TextureFactory texFactory, unsigned pointNumber, double xMin, double xMax, double zMin, double zMax) : PointBasedAlgorythmGenerator(texFactory, pointNumber){
	limitPoints.push_back(Point(xMin, zMin));
	limitPoints.push_back(Point(xMin, zMax));
	limitPoints.push_back(Point(xMax, zMax));
	limitPoints.push_back(Point(xMax, zMin));
}

PointBasedAlgorythmGenerator::PointBasedAlgorythmGenerator(TextureFactory texFactory, unsigned pointNumber) {
	this->pointNumber = pointNumber;
	this->texFactory = texFactory;
}

std::vector<double> PointBasedAlgorythmGenerator::findXLimits(double z) {
	std::vector<double> result;
	showDebug("find limits");
	for (unsigned i = 1; i <= limitPoints.size(); ++i) {
		double z1 = limitPoints[i - 1].z;
		double x1 = limitPoints[i - 1].x;
		double z2 = limitPoints[i % limitPoints.size()].z;
		double x2 = limitPoints[i % limitPoints.size()].x;
		if (z < z2 && z >= z1 || z > z2 && z <= z1
			|| z <= z2 && z > z1 || z >= z2 && z < z1) {
			result.push_back(x1 + (x2 - x1) * (z - z1) / (z2 - z1));
			showDebug(result[result.size() - 1]);
		}
	}
	std::sort(result.begin(), result.end());
	showDebug("size: " + std::to_string(result.size()));
	return result;
}

void PointBasedAlgorythmGenerator::randomPoints() {
	Point zMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	for (size_t i = 0; i < pointNumber; ++i) {
		double z = randomFactory.getLinearValue(zMin.z, zMax.z);
		auto xLimits = findXLimits(z);
		if (xLimits.size() < 2) {
			--i;
			continue;
		}
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
		if (xLimits.size() < 2) {
			--i;
			continue;
		}
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
		if (xLimits.size() < 2) 
			continue;
		for (double x = curXLimits[0]; x < curXLimits[1]; x += step2) {
			double val = noise.GetNoise((float)x, (float)z);
			if (val > limit) {
				roadsPoints.push_back(Point(x, z));
			}
		}
	}
	//showDebug("limit:"+std::to_string(limit) + "   punkty:" + std::to_string(roadsPoints.size()));
}

void PointBasedAlgorythmGenerator::randomNoiseGeneratedPoints() {
	Point zMin = *std::min_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(limitPoints.begin(), limitPoints.end(), [](Point a, Point b) {return a.z < b.z; });
	double step = (zMax.z -zMin.z) / sqrt(pointNumber);
	showDebug("Info z random noise");
	showDebug(pointNumber);
	showDebug(step);
	showDebug(step/3);
	for (double z = zMin.z; z < zMax.z; z += step) {
		auto curXLimits = findXLimits(z);
		for (double x = curXLimits[0]; x < curXLimits[1]; x += step) {
			double randX = randomFactory.getNormalValue(0, step / 3);
			double randZ = randomFactory.getNormalValue(0, step / 3);
			roadsPoints.push_back(Point(x + randX, z + randZ));
		}
	}
	//showDebug("limit:"+std::to_string(limit) + "   punkty:" + std::to_string(roadsPoints.size()));
}

std::vector<Street*> PointBasedAlgorythmGenerator::generate() {
	showDebug("random points");
	if (type == "random")
		randomPoints();
	else if (type == "fastNoise")
		randomFastNoicePoints();
	else if (type == "noise")
		randomNoiseGeneratedPoints();
	else
		randomMinDistPoints(15, 30);
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
			//if (intersects(*i, *j) && !((*i).hasBridges() || (*j).hasBridges())) {
				double l1 = Vector3::countSectionLength(*i);
				double l2 = Vector3::countSectionLength(*j);
				if (canBeReplacedByBridge(*i, *j)) {
					showDebug("mamy to");
					showDebug(roadConnections.size());
					RoadConnection* toReplace = l1 > l2 ? &*i : &*j;
					Point intersection = intersectionPoint(*i, *j);
					toReplace->bridges.push_back(intersection);
					(l1 > l2 ? &*j : &*i)->bridge = true;
				} else {
					// usuwamy krotsza droge
					if (canBeDeleted(j - roadConnections.begin()) && l1 > l2 || !canBeDeleted(i - roadConnections.begin())) {
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
		}
		if (!firstErased) {
			++i;
		}
		else {
			firstErased = false;
			i = roadConnections.begin();
		}
	}
}

bool PointBasedAlgorythmGenerator::canBeReplacedByBridge(RoadConnection a, RoadConnection b) {
	if (a.hasBridges() || b.hasBridges())
		return false;
	Point intersection = intersectionPoint(a, b);
	auto l1 = Vector3::countSectionLength(a.first, intersection);
	auto l2 = Vector3::countSectionLength(a.second, intersection);
	auto l3 = Vector3::countSectionLength(b.second, intersection);
	auto l4 = Vector3::countSectionLength(b.second, intersection);
	double minDist = 2.5;
	return l1 > minDist && l2 > minDist && l3 > minDist && l4 > minDist;
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
						if (canBeDeleted(thisCrossingRoadsIDs[j]) && l1 > l2 || !canBeDeleted(thisCrossingRoadsIDs[i]))
							toDeleteCrossingRoadsIDs.push_back(thisCrossingRoadsIDs[j]);
						else
							toDeleteCrossingRoadsIDs.push_back(thisCrossingRoadsIDs[i]);
						//if (canBeDeleted(thisCrossingRoadsIDs[j]) && canBeDeleted(thisCrossingRoadsIDs[i]))
						//	if (l1 > l2)
						//		toDeleteCrossingRoadsIDs.push_back(thisCrossingRoadsIDs[j]);
						//	else
						//		toDeleteCrossingRoadsIDs.push_back(thisCrossingRoadsIDs[i]);
						//else
						//	if (canBeDeleted(thisCrossingRoadsIDs[j]))
						//		toDeleteCrossingRoadsIDs.push_back(thisCrossingRoadsIDs[j]);
						//	else
						//		toDeleteCrossingRoadsIDs.push_back(thisCrossingRoadsIDs[i]);				
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
				roadConnections.push_back(RoadConnection(p, q));
				++roadCount;
			}
		}
	}
}

void PointBasedAlgorythmGenerator::setUndeletableRoadConnectionIndex(unsigned a) {
	this->undeletableRoadConnectionIndex = a;
}

bool PointBasedAlgorythmGenerator::canBeDeleted(unsigned roadConnectionId) {
	return roadConnectionId >= undeletableRoadConnectionIndex;
}

void PointBasedAlgorythmGenerator::setType(std::string type) {
	this->type = type;
}