#include "Building.h"

Building::Building()
{
}


Building::~Building()
{
	for (unsigned long i = 0; i < prims.size(); ++i) {
		delete prims[i];
	}
}

void Building::setAsCuboid(int moveX, int moveZ)
{
	prims.clear();
	auto primitive = new Primitive();
	primitive->setAsCuboid(moveX, moveZ);
	prims.push_back(primitive);
}

void Building::move(double moveX, double moveY, double moveZ) {
	for (auto prim : prims) 
		prim->move(moveX, moveY, moveZ);
}

void Building::scale(double scaleX, double scaleY, double scaleZ) {
	for (auto prim : prims)
		prim->scale(scaleX, scaleY, scaleZ);
}

void Building::scale(double scale) {
	this->scale(scale, scale, scale);
}

void Building::rotateY(double degrees) {
	for (auto prim : prims)
		prim->rotateY(degrees);
}