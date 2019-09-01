#pragma once

#include <vector>
#include <random>

#include "Building.h"

std::vector<Building*> generateManhatanStyle(int n, int m);
std::vector<Building*> generateParisStyle(int circles);
Building* setRandomHeight(Building* buil);