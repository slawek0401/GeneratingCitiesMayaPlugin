#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <maya\MFloatArray.h>
#include <maya\MGlobal.h>
#include <cmath>

class Primitive
{
public:
public:
	MFloatPointArray vert;
	MIntArray polCounts;
	MIntArray polConnects;
	MFloatArray uArray;
	MFloatArray vArray;
	MIntArray UVids;
	MIntArray UVcounts;

	Primitive();
	~Primitive();

	void setAsCuboid(int moveX, int moveZ);
	void move(double moveX, double moveY, double moveZ);
	void scale(double scaleX, double scaleY, double scaleZ);
	void scale(double scale);
	void rotateY(double degrees);
	MFloatPointArray getVert();
	MIntArray getpolCounts();
	MIntArray getpolConnects();
	MFloatArray getUArray();
	MFloatArray getVArray();
	MIntArray getUVids();
	MIntArray getUVcounts();
	void setNewHeight(double height);
};

