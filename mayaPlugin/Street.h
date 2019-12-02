#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <cmath>

#include "Primitive.h"

class Street : public Primitive
{
public:
	Street(int x1 = 1, int z1 = 1, int width = 2, int length = 2);
	~Street();
};

