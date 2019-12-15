#include "Pyramid.h"



Pyramid::Pyramid(double moveX, double moveY, double moveZ)
{/*
 PODGL¥D
				 2
			  / / \ \
			4--/---\--3
		   / /     \ /
		  0---------1
 */
	vert.append(MFloatPoint(-1 + moveX, 0 + moveY, 1 + moveZ));  //0
	vert.append(MFloatPoint(1 + moveX, 0 + moveY, 1 + moveZ)); //1
	vert.append(MFloatPoint(0 + moveX, 2 + moveY, 0 + moveZ)); //2
	vert.append(MFloatPoint(1 + moveX, 0 + moveY, -1 + moveZ)); //3
	vert.append(MFloatPoint(-1 + moveX, 0 + moveY, -1 + moveZ));  //4


	polCounts.append(4);
	for (int i = 0; i < 4; ++i)
		polCounts.append(3);

	polConnects.append(1);//bottom
	polConnects.append(0);
	polConnects.append(4);
	polConnects.append(3);

	polConnects.append(0);//front
	polConnects.append(1);
	polConnects.append(2);

	polConnects.append(3);//back
	polConnects.append(4);
	polConnects.append(2);

	polConnects.append(4);//left
	polConnects.append(0);
	polConnects.append(2);

	polConnects.append(1);//right
	polConnects.append(3);
	polConnects.append(2);

	oneTextureOnWhole = true;
	float u[6] = {
			0.0, 20.0, 10.0,
			0.0, 20.0, 10.0
	};
	float v[6] = {
			0.0, 0.0, 20.0,
			0.0, 0.0, 20.0
	};
	int ids[18] = {
			0,0,0,0,//bottom
			0,1,2,//front
			0,1,2,//back
			3,4,5,//left
			3,4,5//right
	};
	xTexCoordsIndexFrom = 0;
	xTexCoordsIndexTo = 3;
	zTexCoordsIndexFrom = 3;
	zTexCoordsIndexTo = 6;
	UVcounts.append(4);
	for (int i = 0; i < 4; ++i)
		UVcounts.append(3);
	for (int i = 0; i < 4 + 3 * 4; ++i)
		UVids.append(ids[i]);
	for (int i = 0; i < 6; ++i)
		uArray.append(u[i]);
	for (int i = 0; i < 6; ++i)
		vArray.append(v[i]);
}

Pyramid::~Pyramid()
{
}
