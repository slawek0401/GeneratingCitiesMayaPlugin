#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <cmath>

class Street
{
public:
	MFloatPointArray vert;
	MIntArray polCounts;
	MIntArray polConnects;

	Street(int x1 = 1, int z1 = 1, int width = 2, int length = 2);
	~Street();
};

