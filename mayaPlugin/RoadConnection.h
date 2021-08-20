#pragma once

#include "Point.h"

class RoadConnection
{
public:
	Point first, second;
	double width = 2;
	
	RoadConnection() {}
	RoadConnection(Point first, Point second);
	RoadConnection(Point first, Point second, double width);
};

