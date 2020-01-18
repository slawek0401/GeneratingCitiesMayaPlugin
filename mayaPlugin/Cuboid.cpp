#include "Cuboid.h"



Cuboid::Cuboid(double moveX, double moveZ)
{
	/*
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

	polConnects.append(0);//front
	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(3);

	polConnects.append(5);//back
	polConnects.append(4);
	polConnects.append(7);
	polConnects.append(6);

	polConnects.append(4);//top
	polConnects.append(5);
	polConnects.append(1);
	polConnects.append(0);

	polConnects.append(1);//left
	polConnects.append(5);
	polConnects.append(6);
	polConnects.append(2);

	polConnects.append(3);//bottom
	polConnects.append(2);
	polConnects.append(6);
	polConnects.append(7);

	polConnects.append(4);//right
	polConnects.append(0);
	polConnects.append(3);
	polConnects.append(7);

	/*float u[14] = {
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
	};*/
	oneTextureOnWhole = true;
	float u[8] = {
			0.0, 2.0, 2.0, 0.0,
			0.0, 2.0, 2.0, 0.0
	};
	float v[8] = {
			0.0, 0.0, 7.0, 7.0,
			0.0, 0.0, 7.0, 7.0
	};
	int ids[24] = {
			2,3,0,1,//front
			2,3,0,1,//back
			0,0,0,0,//top
			6,7,4,5,//left
			0,0,0,0,//bottom
			6,7,4,5//right
	};
	xTexCoordsIndexFrom = 0;
	xTexCoordsIndexTo = 4;
	zTexCoordsIndexFrom = 4;
	zTexCoordsIndexTo = 8;
	for (int i = 0; i < 6; ++i)
		UVcounts.append(4);
	for (int i = 0; i < 6 * 4; ++i)
		UVids.append(ids[i]);
	for (int i = 0; i < 8; ++i)
		uArray.append(u[i]);
	for (int i = 0; i < 8; ++i)
		vArray.append(v[i]);
}


Cuboid::~Cuboid()
{
}
