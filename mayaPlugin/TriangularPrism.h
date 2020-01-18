#pragma once
#include "Primitive.h"
class TriangularPrism :
	public Primitive
{
public:
	TriangularPrism(double moveX, double moveY, double moveZ);
	~TriangularPrism();

	void assignTexture(Texture walls, Texture roof);
};

