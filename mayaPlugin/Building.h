#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>

class Building
{
public:
	MFloatPointArray vert;
	MIntArray polCounts;
	MIntArray polConnects;

	Building();
	~Building();

	void setAsCuboid(int moveX, int moveZ);
	MFloatPointArray getVert();
	MIntArray getpolCounts();
	MIntArray getpolConnects();
};