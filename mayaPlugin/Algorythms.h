#pragma once

#include <vector>

#include "RandomFactory.h"
#include "Building.h"
#include "Street.h"

std::vector<Building*> generateManhatanStyle(int n, int m);
std::vector<Building*> generateParisStyle(int circles);
Building* setRandomHeight(Building* buil);
Building* setRandomRoofAngle(Building* building, int percentageProbability);

std::vector<Building*> getBuildingsAlongStreets(std::vector<Street*> streets);
void getBuildingsAlongOneSideOfStreet(std::vector<Building*> &vec, MFloatPoint v1, MFloatPoint v2);
bool isBetween(MFloatPoint a, MFloatPoint x1, MFloatPoint x2);
//streets
std::vector<Street*> getStreetSystem();
std::vector<Street*> getManhatanStreetSystem();