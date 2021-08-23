#pragma once

#include <vector>
#include "Point.h"

class RoadConnection
{
public:
	Point first, second;
	double width = 2;
	bool bridge = false;
	std::vector<Point> bridges;
	
	RoadConnection() {}
	RoadConnection(Point first, Point second);
	RoadConnection(Point first, Point second, double width);
	bool hasBridges() {
		return bridges.size() != 0;
	}
};

