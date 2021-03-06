#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <cmath>
#include "Primitive.h"
#include <vector>

class Building
{
public:
	std::vector<Primitive*> prims;
	std::vector<MFloatPoint> front;

	Building();
	~Building();

	void setAsCuboid(int moveX=0, int moveZ=0);
	void addPrimitive(Primitive* primitive);
	void addMainPrimitive(Primitive* primitive);
	void move(double moveX, double moveY, double moveZ);
	void scale(double scaleX, double scaleY, double scaleZ);
	void scale(double scale);
	void rotateY(double degrees);
	double frontWidth();
	void setNewHeight(double height);
	double getHeight();
	void assignMainTexture(Texture tex);
};