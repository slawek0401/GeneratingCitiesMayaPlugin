#include "FractalGenerator.h"


typedef struct mapParam {
	bool foundOnLeft = false;
	bool foundOnRight = false;
};

FractalGenerator::FractalGenerator(TextureFactory texFactory, double xMin, double xMax, double zMin, double zMax) {
	this->texFactory = texFactory;
	this->limitPoints.push_back(Point(xMin, zMin));
	this->limitPoints.push_back(Point(xMin, zMax));
	this->limitPoints.push_back(Point(xMax, zMax));
	this->limitPoints.push_back(Point(xMax, zMin));
}

std::vector<Street*> FractalGenerator::generate() {
	addCrossings();
	addStreets();
	return this->streets;
}

FractalGenerator& FractalGenerator::addGenerator(GeneratorAbstract& generator) {
	generator.setIgnoreVisualObjects(true);
	if (isFirstAlg) {
		isFirstAlg = false;
		generator.limitPoints = this->limitPoints;
		generator.generate();
		this->roadConnections = generator.roadConnections;
		this->roadsPoints = generator.roadsPoints;
	} else {
		auto newLimits = countNewLimitPoints();
		for (auto limit : newLimits) {
			generator.limitPoints = limit;
			generator.generate();
			addAll<>(this->roadConnections, generator.roadConnections);
			addAll<>(this->roadsPoints, generator.roadsPoints);
		}
	}
	return *this;
}

std::vector<std::vector<Point>> FractalGenerator::countNewLimitPoints() {
	std::vector<std::vector<Point>> result;
	std::map<unsigned, mapParam> roadMap;
	for (unsigned i = 0; i < roadConnections.size(); ++i) {
		auto connection = roadConnections[i];
		if (connection.first < connection.second && roadMap[i].foundOnRight || 
			connection.first > connection.second && roadMap[i].foundOnLeft)
			continue;

		std::vector<Point> currResult;
		currResult.push_back(connection.second);
		unsigned newConnectionId = i;
		connection.first < connection.second ? roadMap[i].foundOnRight = true : roadMap[i].foundOnLeft = true;
		Point currentPoint = connection.first;
		while (currentPoint != connection.second) {
			currResult.push_back(currentPoint);
			auto prevConnectionId = newConnectionId;
			newConnectionId = findAnotherConnectionId(newConnectionId, currentPoint);
			if (prevConnectionId == newConnectionId) // to byla slepa uliczka
				connection.first > connection.second ? roadMap[newConnectionId].foundOnRight = true : roadMap[newConnectionId].foundOnLeft = true;
			connection.first < connection.second ? roadMap[newConnectionId].foundOnRight = true : roadMap[newConnectionId].foundOnLeft = true;
			currentPoint = roadConnections[newConnectionId].first == currentPoint ? roadConnections[newConnectionId].second : roadConnections[newConnectionId].first;
		}
		result.push_back(currResult);
	}
	return result;
}

unsigned FractalGenerator::findAnotherConnectionId(unsigned i, Point p) {
	auto crossingConnectionsIds = findPointsConnections(p);
	auto rc = &roadConnections;
	std::sort(crossingConnectionsIds.begin(), crossingConnectionsIds.end(),
		[p, rc](unsigned a, unsigned b) {
			auto ar1 = (*rc)[a].first == p ? (*rc)[a].second : (*rc)[a].first;
			auto ar2 = (*rc)[b].first == p ? (*rc)[b].second : (*rc)[b].first;
			return comparePointAngle(ar1, ar2, p);
		});
	return crossingConnectionsIds[(findElement<unsigned>(crossingConnectionsIds, i) + 1) % crossingConnectionsIds.size()];
}

std::vector<unsigned> FractalGenerator::findPointsConnections(Point p) {
	std::vector<unsigned> roadConnectioIds;
	for (unsigned i = 0; i < roadConnections.size(); ++i) 
		if (roadConnections[i].first == p || roadConnections[i].second == p)
			roadConnectioIds.push_back(i);
	return roadConnectioIds;
}