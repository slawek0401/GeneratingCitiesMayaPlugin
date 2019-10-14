#pragma once

#include <vector>
#include <random>

#include "Building.h"
#include "Street.h"

std::vector<Building*> generateManhatanStyle(int n, int m);
std::vector<Building*> generateParisStyle(int circles);
Building* setRandomHeight(Building* buil);
Building* setRandomRoofAngle(Building* building, int percentageProbability);
std::vector<Street*> getStreetSystem();
std::vector<Building*> getBuildingsAlongStreets(std::vector<Street*> streets);
bool isBetween(MFloatPoint a, MFloatPoint x1, MFloatPoint x2);