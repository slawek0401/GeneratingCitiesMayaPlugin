#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <cmath>

class Building
{
public:
	MFloatPointArray vert;
	MIntArray polCounts;
	MIntArray polConnects;

	Building();
	~Building();

	void setAsCuboid(int moveX, int moveZ);
	void move(double moveX, double moveY, double moveZ);
	void scale(double scaleX, double scaleY, double scaleZ);
	void scale(double scale);
	void rotateY(double degrees);
	MFloatPointArray getVert();
	MIntArray getpolCounts();
	MIntArray getpolConnects();
};