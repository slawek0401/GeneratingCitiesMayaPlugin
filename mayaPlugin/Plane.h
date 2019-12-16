#pragma once
#include "Primitive.h"
class Plane :
	public Primitive
{
public:
	Plane(int x1, int z1, int width, int length);
	~Plane();
};

