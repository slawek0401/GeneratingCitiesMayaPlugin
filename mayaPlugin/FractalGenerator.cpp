#include "FractalGenerator.h"

FractalGenerator::FractalGenerator(TextureFactory texFactory, double xMin, double xMax, double zMin, double zMax) {
	this->texFactory = texFactory;
	this->limitPoints.push_back(Point(xMin, zMin));
	this->limitPoints.push_back(Point(xMin, zMax));
	this->limitPoints.push_back(Point(xMax, zMax));
	this->limitPoints.push_back(Point(xMax, zMin));
	this->countCityDiagonal();
}

std::vector<Street*> FractalGenerator::generate() {
	addCrossings();
	addStreets();
	return this->streets;
}

void showLimits(std::vector<std::vector<Point>> limits) {
	showDebug("limits size" + std::to_string(limits.size()));
	for (auto limit : limits) {
		showDebug("   limit " " size" + std::to_string(limit.size()));
		for (auto p : limit) {
			showDebug("        point x:" + std::to_string(p.x) + " y:" + std::to_string(p.y) + " z:" + std::to_string(p.z));
		}

	}
}

FractalGenerator& FractalGenerator::addGenerator(PointBasedAlgorythmGenerator& generator) {
	showDebug("addGenerator");
	generator.setIgnoreVisualObjects(true);
	generator.setCityDiagonal(this->getCityDiagonal());
	if (isFirstAlg) {
		isFirstAlg = false;
		generator.limitPoints = this->limitPoints;
		generator.generate();
		this->roadConnections = generator.roadConnections;
		this->roadsPoints = generator.roadsPoints;
	} else {
		showDebug("przed count limit");
		auto newLimits = countNewLimitPoints();
		showDebug("po count limit");
		showLimits(newLimits);
		for (auto limit : newLimits) 
			if (limit.size() >= 3) {
				std::reverse(limit.begin(), limit.end());
				generator.limitPoints = limit;
				generator.roadConnections = computeRoadConnectionFromLimitPoints(limit);
				generator.setUndeletableRoadConnectionIndex(limit.size());
				addAll<>(generator.roadsPoints, limit);
				generator.generate();
				double streetWidth = generator.streetWidth;
				std::for_each(generator.roadConnections.begin() + limit.size(), generator.roadConnections.end(), [streetWidth](RoadConnection& a) {a.width = streetWidth; });
				addAllFromIndex<>(this->roadConnections, generator.roadConnections, limit.size());
				addAllFromIndex<>(this->roadsPoints, generator.roadsPoints, limit.size());
				generator.roadConnections.clear();
				generator.roadsPoints.clear();
			}
	}
	return *this;
}

FractalGenerator& FractalGenerator::addGenerator(BinaryDivisionAlgorythmGenerator& generator) {
	showDebug("addGenerator");
	generator.setIgnoreVisualObjects(true);
	generator.setCityDiagonal(this->getCityDiagonal());
	if (isFirstAlg) {
		isFirstAlg = false;
		generator.limitPoints = this->limitPoints;
		generator.generate();
		this->roadConnections = generator.roadConnections;
		this->roadsPoints = generator.roadsPoints;
	}
	else {
		showDebug("przed count limit");
		auto newLimits = countNewLimitPoints();
		showDebug("po count limit");
		showLimits(newLimits);
		for (auto limit : newLimits)
			if (limit.size() >= 4) {
				std::reverse(limit.begin(), limit.end());
				countNewLimitPointsForBinary(limit, generator);
				generator.generate();
				addAll<>(this->roadConnections, generator.roadConnections);
				addAll<>(this->roadsPoints, generator.roadsPoints);
				generator.roadConnections.clear();
				generator.roadsPoints.clear();
			}
	}
	return *this;
}

std::vector<RoadConnection> FractalGenerator::computeRoadConnectionFromLimitPoints(std::vector<Point> limit) {
	std::vector<RoadConnection> result;
	for (unsigned i = 0; i < limit.size(); ++i) 
		result.push_back(RoadConnection(limit[i], limit[( i + 1 ) % limit.size()]));
	return result;
}

void FractalGenerator::countNewLimitPointsForBinary(std::vector<Point> currLimit, BinaryDivisionAlgorythmGenerator& generator) {
	auto pairX = std::minmax_element(currLimit.begin(), currLimit.end(), [](Point a, Point b) {return a.x < b.x; });
	auto pairZ = std::minmax_element(currLimit.begin(), currLimit.end(), [](Point a, Point b) {return a.z < b.z; });
	generator.xMin = (*(pairX.first)).x;
	generator.xMax = (*(pairX.second)).x;
	generator.zMin = (*(pairZ.first)).z;
	generator.zMax = (*(pairZ.second)).z;
}

std::vector<std::vector<Point>> FractalGenerator::countNewLimitPoints() {
	std::vector<std::vector<Point>> result;
	std::map<unsigned, mapParam> roadMap = initializeMap();

	for (unsigned i = 0; i < roadConnections.size(); ++i) {
		auto connection = roadConnections[i];
		if (roadMap[i].foundOnLeft)
			continue;

		std::vector<Point> currResult;
		currResult.push_back(connection.second);
		unsigned newConnectionId = i;
		roadMap[i].foundOnLeft = true;
		Point currentPoint = connection.first;
		auto firstConnection = connection;
		while (currentPoint != firstConnection.second) {
			currResult.push_back(currentPoint);
			auto prevConnectionId = newConnectionId;
			newConnectionId = findAnotherConnectionId(newConnectionId, currentPoint);
			connection = roadConnections[newConnectionId];
			if (prevConnectionId == newConnectionId) // to byla slepa uliczka
				connection.second == currentPoint ? roadMap[newConnectionId].foundOnRight = true : roadMap[newConnectionId].foundOnLeft = true;
			connection.first == currentPoint ? roadMap[newConnectionId].foundOnRight = true : roadMap[newConnectionId].foundOnLeft = true;
			currentPoint = roadConnections[newConnectionId].first == currentPoint ? roadConnections[newConnectionId].second : roadConnections[newConnectionId].first;
		}
		result.push_back(currResult);
	}
	return result;
}

unsigned FractalGenerator::findAnotherConnectionId(unsigned i, Point p, bool left) {
	auto crossingConnectionsIds = findPointsConnections(p);
	auto rc = &roadConnections;
	std::sort(crossingConnectionsIds.begin(), crossingConnectionsIds.end(),
		[p, rc](unsigned a, unsigned b) {
			auto ar1 = (*rc)[a].first == p ? (*rc)[a].second : (*rc)[a].first;
			auto ar2 = (*rc)[b].first == p ? (*rc)[b].second : (*rc)[b].first;
			return comparePointAngle(ar1, ar2, p);
		});
	if (left)
		return crossingConnectionsIds[(findElement<unsigned>(crossingConnectionsIds, i) + crossingConnectionsIds.size() - 1) % crossingConnectionsIds.size()];
	else
		return crossingConnectionsIds[(findElement<unsigned>(crossingConnectionsIds, i) + 1) % crossingConnectionsIds.size()];
}

std::vector<unsigned> FractalGenerator::findPointsConnections(Point p) {
	std::vector<unsigned> roadConnectioIds;
	for (unsigned i = 0; i < roadConnections.size(); ++i) 
		if (roadConnections[i].first == p || roadConnections[i].second == p)
			roadConnectioIds.push_back(i);
	return roadConnectioIds;
}

std::map<unsigned, mapParam> FractalGenerator::initializeMap() {
	if (isMapInitialized)
		return this->roadBoundariesMap;
	Point firstPoint = *std::min_element(this->roadsPoints.begin(), this->roadsPoints.end());
	auto connections = findPointsConnections(firstPoint);
	auto rc = &roadConnections;
	std::sort(connections.begin(), connections.end(),
		[firstPoint, rc](unsigned a, unsigned b) {
			auto ar1 = (*rc)[a].first == firstPoint ? (*rc)[a].second : (*rc)[a].first;
			auto ar2 = (*rc)[b].first == firstPoint ? (*rc)[b].second : (*rc)[b].first;
			return comparePointAngle(ar1, ar2, firstPoint);
		});
	
	unsigned newConnectionId = connections[connections.size() - 1];
	//unsigned newConnectionId = connections[0];
	auto firstConnection = roadConnections[newConnectionId];
	firstConnection.second == firstPoint ? roadBoundariesMap[newConnectionId].foundOnRight = true : roadBoundariesMap[newConnectionId].foundOnLeft = true;
	showDebug("initializing map");
	showDebug("   "+std::to_string(firstConnection.first.x) + " " + std::to_string(firstConnection.first.z) + "   " + std::to_string(firstConnection.second.x) + " " + std::to_string(firstConnection.second.z));

	Point currentPoint = firstPoint;
	while (currentPoint != firstConnection.second) {
		auto prevConnectionId = newConnectionId;
		newConnectionId = findAnotherConnectionId(newConnectionId, currentPoint/*, true*/);
		auto connection = roadConnections[newConnectionId];
		if (prevConnectionId == newConnectionId) // to byla slepa uliczka
			connection.second == currentPoint ? roadBoundariesMap[newConnectionId].foundOnRight = true : roadBoundariesMap[newConnectionId].foundOnLeft = true;
		connection.first == currentPoint ? roadBoundariesMap[newConnectionId].foundOnRight = true : roadBoundariesMap[newConnectionId].foundOnLeft = true;
		currentPoint = roadConnections[newConnectionId].first == currentPoint ? roadConnections[newConnectionId].second : roadConnections[newConnectionId].first;
		showDebug("   " + std::to_string(connection.first.x) + " " + std::to_string(connection.first.z) + "   " + std::to_string(connection.second.x) + " " + std::to_string(connection.second.z));
	}
	return this->roadBoundariesMap;
}