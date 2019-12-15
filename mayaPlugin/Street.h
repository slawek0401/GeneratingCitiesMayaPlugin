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

public:
	Street(BuildingType neighbourhood, int x1 = 1, int z1 = 1, int width = 2, int length = 2);
	~Street();

	void addBuildingAlongAbsolute(MFloatPoint from, MFloatPoint to);
	void addBuildingAlongRelative(float from, float to, bool left);
	void addBuildingAlongAllStreet();
	std::vector<MFloatPoint> getBuildingsAlong();
	BuildingType getNeighbourhood();
	void setNeighbourhood(BuildingType bType);
};

