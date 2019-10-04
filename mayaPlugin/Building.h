#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <cmath>
#include "Primitive.h"
#include <vector>

class Building
{
public:
	std::vector<Primitive*> prims;

	Building();
	~Building();

	void setAsCuboid(int moveX, int moveZ);
	void move(double moveX, double moveY, double moveZ);
	void scale(double scaleX, double scaleY, double scaleZ);
	void scale(double scale);
	void rotateY(double degrees);
};