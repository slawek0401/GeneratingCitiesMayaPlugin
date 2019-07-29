#include "Building.h"

Building::Building()
{
}


Building::~Building()
{
}

MFloatPointArray Building::getVert() {
	return vert;
}

MIntArray Building::getpolCounts() {
	return polCounts;
}

MIntArray Building::getpolConnects() {
	return polConnects;
}

void Building::setAsCuboid(int moveX, int moveZ)
{
	vert.append(MFloatPoint(1 + moveX, 5, 1 + moveZ));
	vert.append(MFloatPoint(-1 + moveX, 5, 1 + moveZ));
	vert.append(MFloatPoint(-1 + moveX, 0, 1 + moveZ));
	vert.append(MFloatPoint(1 + moveX, 0, 1 + moveZ));
	vert.append(MFloatPoint(1 + moveX, 5, -1 + moveZ));
	vert.append(MFloatPoint(-1 + moveX, 5, -1 + moveZ));
	vert.append(MFloatPoint(-1 + moveX, 0, -1 + moveZ));
	vert.append(MFloatPoint(1 + moveX, 0, -1 + moveZ));


	for (int i = 0; i < 6; ++i)
		polCounts.append(4);
	
	polConnects.append(0);
	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(3);

	polConnects.append(4);
	polConnects.append(5);
	polConnects.append(6);
	polConnects.append(7);

	polConnects.append(0);
	polConnects.append(1);
	polConnects.append(5);
	polConnects.append(4);

	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(6);
	polConnects.append(5);

	polConnects.append(2);
	polConnects.append(3);
	polConnects.append(7);
	polConnects.append(6);

	polConnects.append(0);
	polConnects.append(3);
	polConnects.append(7);
	polConnects.append(4);
}

void Building::move(double moveX, double moveY, double moveZ) {
	for (int i = 0; i < vert.sizeIncrement(); ++i) {
		vert[i].x += moveX;
		vert[i].y += moveY;
		vert[i].z += moveZ;
	}
}

void Building::scale(double scaleX, double scaleY, double scaleZ) {
	for (int i = 0; i < vert.sizeIncrement(); ++i) {
		vert[i].x *= scaleX;
		vert[i].y *= scaleY;
		vert[i].z *= scaleZ;
	}
}

void Building::scale(double scale) {
	this->scale(scale, scale, scale);
}

void Building::rotateY(double degrees) {
	double degInRad = degrees * M_PI / 180;
	for (int i = 0; i < vert.sizeIncrement(); ++i) {
		auto oldX = vert[i].x;
		auto oldZ = vert[i].z;
		vert[i].x = cos(degInRad) * oldX - sin(degInRad) * oldZ;
		vert[i].z = sin(degInRad) * oldX + cos(degInRad) * oldZ;
	}
}