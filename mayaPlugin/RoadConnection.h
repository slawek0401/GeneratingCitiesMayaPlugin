#pragma once

#include <vector>
#include "Point.h"

class RoadConnection
{
public:
	Point first, second;
	double width = 2;
	std::vector<Point> bridges;
	std::vector<bool> isUnderBrigde;
	
	RoadConnection() {}
	RoadConnection(Point first, Point second);
	RoadConnection(Point first, Point second, double width);
	bool hasBridges() {
		return bridges.size() != 0;
	}
	bool hasUnderBridges() {
		for (auto u : isUnderBrigde) 
			if (u)
				return true;
		return false;
	}
};

