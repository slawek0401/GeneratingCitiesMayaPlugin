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
	front.push_back(primitive->vert[6]);
	front.push_back(primitive->vert[7]);
}

void Building::addPrimitive(Primitive* primitive) {
	prims.push_back(primitive);
}

void Building::addMainPrimitive(Primitive* primitive) {
	prims.push_back(primitive);
	front.push_back(primitive->vert[6]);
	front.push_back(primitive->vert[7]);
}

void Building::move(double moveX, double moveY, double moveZ) {
	for (auto prim : prims) 
		prim->move(moveX, moveY, moveZ);
	for (int i = 0; i < front.size(); ++i) {
		front[i].x += moveX;
		front[i].y += moveY;
		front[i].z += moveZ;
	}
}

void Building::scale(double scaleX, double scaleY, double scaleZ) {
	for (auto prim : prims)
		prim->scale(scaleX, scaleY, scaleZ);
	for (int i = 0; i < front.size(); ++i) {
		front[i].x *= scaleX;
		front[i].y *= scaleY;
		front[i].z *= scaleZ;
	}
}

void Building::scale(double scale) {
	this->scale(scale, scale, scale);
}

void Building::rotateY(double degrees) {
	for (auto prim : prims)
		prim->rotateY(degrees);
	double degInRad = degrees * M_PI / 180;
	for (int i = 0; i < front.size(); ++i) {
		auto oldX = front[i].x;
		auto oldZ = front[i].z;
		front[i].x = cos(degInRad) * oldX - sin(degInRad) * oldZ;
		front[i].z = sin(degInRad) * oldX + cos(degInRad) * oldZ;
	}
}

double Building::frontWidth() {
	return sqrt((front[0].x - front[1].x) * (front[0].x - front[1].x) + (front[0].y - front[1].y) * (front[0].y - front[1].y));
}

void Building::setNewHeight(double height) {
	for (auto prim : prims)
		prim->setNewScaleHeight(height);
}

double Building::getHeight() {
	double maxHeight = 0.0;
	for (auto prim : prims) {
		double currHeight = prim->getHeight();
		if (maxHeight < currHeight)
			maxHeight = currHeight;
	}
	return maxHeight;
}

void Building::assignMainTexture(Texture tex) {
	prims[0]->assignTexture(tex);
}