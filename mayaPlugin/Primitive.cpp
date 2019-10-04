#include "Primitive.h"

Primitive::Primitive()
{
}


Primitive::~Primitive()
{
}

MFloatPointArray Primitive::getVert() {
	return vert;
}

MIntArray Primitive::getpolCounts() {
	return polCounts;
}

MIntArray Primitive::getpolConnects() {
	return polConnects;
}

void Primitive::setAsCuboid(int moveX, int moveZ)
{/*
			1---------0
		   /|        /|
		  5---------4 |
		  |	|	    | |
		  |	|    	| |
		  |	2-------|-3
		  |/        |/
		  6---------7
 */
	vert.append(MFloatPoint(1 + moveX, 5, 1 + moveZ));  //0
	vert.append(MFloatPoint(-1 + moveX, 5, 1 + moveZ)); //1
	vert.append(MFloatPoint(-1 + moveX, 0, 1 + moveZ)); //2
	vert.append(MFloatPoint(1 + moveX, 0, 1 + moveZ));  //3
	vert.append(MFloatPoint(1 + moveX, 5, -1 + moveZ)); //4
	vert.append(MFloatPoint(-1 + moveX, 5, -1 + moveZ));//5
	vert.append(MFloatPoint(-1 + moveX, 0, -1 + moveZ));//6
	vert.append(MFloatPoint(1 + moveX, 0, -1 + moveZ)); //7


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

void Primitive::move(double moveX, double moveY, double moveZ) {
	for (int i = 0; i < vert.sizeIncrement(); ++i) {
		vert[i].x += moveX;
		vert[i].y += moveY;
		vert[i].z += moveZ;
	}
}

void Primitive::scale(double scaleX, double scaleY, double scaleZ) {
	for (int i = 0; i < vert.sizeIncrement(); ++i) {
		vert[i].x *= scaleX;
		vert[i].y *= scaleY;
		vert[i].z *= scaleZ;
	}
}

void Primitive::scale(double scale) {
	this->scale(scale, scale, scale);
}

void Primitive::rotateY(double degrees) {
	double degInRad = degrees * M_PI / 180;
	for (int i = 0; i < vert.sizeIncrement(); ++i) {
		auto oldX = vert[i].x;
		auto oldZ = vert[i].z;
		vert[i].x = cos(degInRad) * oldX - sin(degInRad) * oldZ;
		vert[i].z = sin(degInRad) * oldX + cos(degInRad) * oldZ;
	}
}