#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <cmath>
#include <vector>

#include "Primitive.h"

class Street : public Primitive
{
	std::vector<MFloatPoint> buildingsAlong;
	BuildingType neighbourhood;
	bool parkOnLeft = false;

public:
	Street(BuildingType neighbourhood, double walkPathFrac, int x1 = 0, int z1 = 0, int width = 2, int length = 2);
	~Street();

	void addBuildingAlongAbsolute(MFloatPoint from, MFloatPoint to);
	void addBuildingAlongRelative(float from, float to, bool left);
	void addBuildingAlongAllStreet();
	std::vector<MFloatPoint> getBuildingsAlong();
	BuildingType getNeighbourhood();
	void setNeighbourhood(BuildingType bType);
	void assignTexture(Texture walkPaths, Texture road);
	void setParkOnLeft();
	bool isParkOnLeft();
};

