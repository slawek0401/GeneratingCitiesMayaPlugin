#pragma once
#include <algorithm>

#include "Street.h"
#include "Point.h"

class Polygon : 
	public Street
{
public:
	Polygon(std::vector<Point> points);
	~Polygon();
};

