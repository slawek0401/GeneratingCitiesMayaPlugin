#include "Primitive.h"

Primitive::Primitive()
{
}


Primitive::~Primitive()
{
}

void Primitive::setAsCuboid(int moveX, int moveZ)
{/*
 PODGL¥D
			5---------4
		   /|        /|
		  1---------0 |
		  |	|	    | |
		  |	|    	| |
		  |	6-------|-7
		  |/        |/
		  2---------3
SIATKA
			2----3
			|	 |
			6----7
			|	 |
			5----4
			|	 |
		5---1----0---4
		|	|	 |	 |
		6---2----3---7
			
SIATKA UV
		   12----13
			|	 |
		   10----11
			|	 |
			8----9
			|	 |
		4---5----6---7
		|	|	 |	 |
		0---1----2---3

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

	polConnects.append(5);
	polConnects.append(4);
	polConnects.append(7);
	polConnects.append(6);

	polConnects.append(4);
	polConnects.append(5);
	polConnects.append(1);
	polConnects.append(0);

	polConnects.append(1);
	polConnects.append(5);
	polConnects.append(6);
	polConnects.append(2);

	polConnects.append(3);
	polConnects.append(2);
	polConnects.append(6);
	polConnects.append(7);

	polConnects.append(4);
	polConnects.append(0);
	polConnects.append(3);
	polConnects.append(7);

	float u[14] = {
			0.0, 0.3333, 0.6667, 1.0,
			0.0, 0.3333, 0.6667, 1.0,
			0.3333, 0.6667, 0.3333, 0.6667, 0.3333, 0.6667
		};
	float v[14] = {
			0.0, 0.0, 0.0, 0.0,
			0.25, 0.25, 0.25, 0.25,
			0.5, 0.5, 0.75, 0.75, 1.0, 1.0
		};
	int ids[24] = {
			6,5,1,2,
			8,9,11,10,
			9,8,5,6,
			5,4,0,1,
			13,12,10,11,
			7,6,2,3
	};
	for (int i = 0; i < 6; ++i)
		UVcounts.append(4);
	for (int i = 0; i < 6 * 4; ++i)
		UVids.append(ids[i]);
	for (int i = 0; i < 14; ++i)
		uArray.append(u[i]);
	for (int i = 0; i < 14; ++i)
		vArray.append(v[i]);
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
MFloatPointArray Primitive::getVert() {
	return vert;
}

MIntArray Primitive::getpolCounts() {
	return polCounts;
}

MIntArray Primitive::getpolConnects() {
	return polConnects;
}
MFloatArray Primitive::getUArray() {
	return uArray;
}
MFloatArray Primitive::getVArray() {
	return vArray;
}
MIntArray Primitive::getUVids() {
	return UVids;
}
MIntArray Primitive::getUVcounts() {
	return UVcounts;
}