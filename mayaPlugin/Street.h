#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <cmath>
#include <vector>

#include "Primitive.h"
#include "Vector3.h"

class Street : public Primitive
{
	std::vector<MFloatPoint> buildingsAlong;
	BuildingType neighbourhood;
	bool parkOnLeft = false;
	double width, length;
	double walkPathFrac;

public:
	Street() {};
	Street(BuildingType neighbourhood, double walkPathFrac = 0.15, double x1=0.0, double z1=0.0, double width=2.0, double length=2.0);
	~Street();

	void addBuildingAlongAbsolute(MFloatPoint from, MFloatPoint to);
	void addBuildingAlongRelative(float from, float to, bool left);
	void addBuildingAlongAllStreet();
	std::vector<MFloatPoint> getBuildingsAlong();
	BuildingType getNeighbourhood();
	void setNeighbourhood(BuildingType bType);
	void assignTexture(Texture walkPaths, Texture road);
	void assignTexture(Texture road);
	void setParkOnLeft();
	bool isParkOnLeft();
	double getWidth();
	double getLength();
	double getWalkPathFrac();
};

