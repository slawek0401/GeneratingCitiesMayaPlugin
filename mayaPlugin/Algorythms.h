#pragma once

#include <vector>

#include "RandomFactory.h"
#include "Building.h"
#include "Street.h"
#include "TextureFactory.h"
#include "BuildingsFactory.h"

std::vector<Building*> generateManhatanStyle(int n, int m);
std::vector<Building*> generateParisStyle(int circles);
Building* setRandomHeight(Building* building);
Building* setRandomWidth(Building* building);

std::vector<Building*> getBuildingsAlongStreets(std::vector<Street*> streets, TextureFactory texFactory);
void getBuildingsAlongOneSideOfStreet(std::vector<Building*> &vec, MFloatPoint v1, MFloatPoint v2, TextureFactory texFactory, BuildingType bType);
bool isBetween(MFloatPoint a, MFloatPoint x1, MFloatPoint x2);
double countSegmentLength(const MFloatPoint& a1, const  MFloatPoint& a2);
MFloatPoint alignAndAdd(const MFloatPoint& v1, const MFloatPoint& v2, Building* b, std::vector<Building*>& vec, const MFloatPoint& curr);
bool turningNeeded(MFloatPoint x, MFloatPoint y, MFloatPoint v, MFloatPoint w);
BuildingType getBuildingTypeByDistanceFromCentre(int cityWidth, int cityLength, int x, int y);

//streets
std::vector<Street*> getStreetSystem();
std::vector<Street*> getManhatanStreetSystem(TextureFactory texFactory);