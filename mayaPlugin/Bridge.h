#pragma once
#include "Street.h"

class Bridge :
	public Street
{
public:
	Bridge(double walkPathFrac = 0.15, double x1 = 0, double z1 = 0, double width = 2, double length = 4, double height = 1, double uprise = 1);
};

