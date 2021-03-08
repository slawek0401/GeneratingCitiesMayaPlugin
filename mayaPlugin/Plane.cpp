#include "Plane.h"

#include <maya/MGlobal.h>

Plane::Plane(int x1, int z1, int width, int length)
{
	/*
	0-----3
	|     |
	|     |
	|     |
	1-----2
	*/

	vert.append(MFloatPoint(x1, 0, z1)); //0
	vert.append(MFloatPoint(x1, 0, z1 + length)); //1
	vert.append(MFloatPoint(x1 + width, 0, z1 + length)); //2
	vert.append(MFloatPoint(x1 + width, 0, z1)); //3

	polCounts.append(4);

	polConnects.append(0);
	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(3);

	oneTextureOnWhole = true;
	
	xTexCoordsIndexFrom = 0;
	xTexCoordsIndexTo = 4;
	zTexCoordsIndexFrom = 0;
	zTexCoordsIndexTo = 4;

	float u[4] = {
			0.0, width * 2, width * 2, 0.0
	};
	float v[4] = {
			0.0, 0.0, length * 2, length * 2
	};
	int ids[] = {
			0,3,2,1,
	};

	UVcounts.append(4);
	for (int i = 0; i < 4; ++i)
		UVids.append(ids[i]);
	for (int i = 0; i < 4; ++i)
		uArray.append(u[i]);
	for (int i = 0; i < 4; ++i)
		vArray.append(v[i]);
}


Plane::~Plane()
{
}
