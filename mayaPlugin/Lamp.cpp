#include "Lamp.h"


Lamp::Lamp(double moveX, double moveZ)
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
	//stojak
	vert.append(MFloatPoint(0.01 + moveX, 1, 0.01 + moveZ));  //0
	vert.append(MFloatPoint(-0.01 + moveX, 1, 0.01 + moveZ)); //1
	vert.append(MFloatPoint(-0.01 + moveX, 0, 0.01 + moveZ)); //2
	vert.append(MFloatPoint(0.01 + moveX, 0, 0.01 + moveZ));  //3
	vert.append(MFloatPoint(0.01 + moveX, 1, -0.01 + moveZ)); //4
	vert.append(MFloatPoint(-0.01 + moveX, 1, -0.01 + moveZ));//5
	vert.append(MFloatPoint(-0.01 + moveX, 0, -0.01 + moveZ));//6
	vert.append(MFloatPoint(0.01 + moveX, 0, -0.01 + moveZ)); //7
	
	vert.append(MFloatPoint(0 + moveX, 1.01, -0.01 + moveZ)); //8
	vert.append(MFloatPoint(0 +moveX, 1.01, 0.01 + moveZ)); //9

	vert.append(MFloatPoint(0.08 + moveX, 1.01, -0.01 + moveZ)); //10
	vert.append(MFloatPoint(0.08 + moveX, 1.01, 0.01 + moveZ)); //11
	vert.append(MFloatPoint(0.08 + moveX, 1.02, -0.01 + moveZ)); //12
	vert.append(MFloatPoint(0.08 + moveX, 1.02, 0.01 + moveZ)); //13

	vert.append(MFloatPoint(-0.08 + moveX, 1.01, -0.01 + moveZ)); //14
	vert.append(MFloatPoint(-0.08 + moveX, 1.01, 0.01 + moveZ)); //15
	vert.append(MFloatPoint(-0.08 + moveX, 1.02, -0.01 + moveZ)); //16
	vert.append(MFloatPoint(-0.08 + moveX, 1.02, 0.01 + moveZ)); //17

	//lampy
	vert.append(MFloatPoint(0.08 + moveX, 1.009, -0.011 + moveZ)); //18
	vert.append(MFloatPoint(0.08 + moveX, 1.009, 0.011 + moveZ)); //19
	vert.append(MFloatPoint(0.08 + moveX, 1.021, -0.011 + moveZ)); //20
	vert.append(MFloatPoint(0.08 + moveX, 1.021, 0.011 + moveZ)); //21
	
	vert.append(MFloatPoint(0.12 + moveX, 1.019, -0.011 + moveZ)); //22
	vert.append(MFloatPoint(0.12 + moveX, 1.019, 0.011 + moveZ)); //23
	vert.append(MFloatPoint(0.12 + moveX, 1.031, -0.011 + moveZ)); //24
	vert.append(MFloatPoint(0.12 + moveX, 1.031, 0.011 + moveZ)); //25

	vert.append(MFloatPoint(-0.08 + moveX, 1.009, -0.011 + moveZ)); //26
	vert.append(MFloatPoint(-0.08 + moveX, 1.009, 0.011 + moveZ)); //27
	vert.append(MFloatPoint(-0.08 + moveX, 1.021, -0.011 + moveZ)); //28
	vert.append(MFloatPoint(-0.08 + moveX, 1.021, 0.011 + moveZ)); //29

	vert.append(MFloatPoint(-0.12 + moveX, 1.019, -0.011 + moveZ)); //30
	vert.append(MFloatPoint(-0.12 + moveX, 1.019, 0.011 + moveZ)); //31
	vert.append(MFloatPoint(-0.12 + moveX, 1.031, -0.011 + moveZ)); //32
	vert.append(MFloatPoint(-0.12 + moveX, 1.031, 0.011 + moveZ)); //33

	
	for (int i = 0; i < 2; ++i)
		polCounts.append(9);
	for (int i = 0; i < 19; ++i)
		polCounts.append(4);

	polConnects.append(0);//front
	polConnects.append(11);
	polConnects.append(13);
	polConnects.append(9);
	polConnects.append(17);
	polConnects.append(15);
	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(3);

	polConnects.append(5);//back
	polConnects.append(14);
	polConnects.append(16);
	polConnects.append(8);
	polConnects.append(12);
	polConnects.append(10);
	polConnects.append(4);
	polConnects.append(7);
	polConnects.append(6);

	polConnects.append(9);//top1
	polConnects.append(8);
	polConnects.append(16);
	polConnects.append(17);

	polConnects.append(13);//top2
	polConnects.append(12);
	polConnects.append(8);
	polConnects.append(9);

	polConnects.append(1);//left
	polConnects.append(5);
	polConnects.append(6);
	polConnects.append(2);

	polConnects.append(4);//right
	polConnects.append(0);
	polConnects.append(3);
	polConnects.append(7);

	polConnects.append(3);//bottom1
	polConnects.append(2);
	polConnects.append(6);
	polConnects.append(7);

	polConnects.append(1);//bottom2
	polConnects.append(15);
	polConnects.append(14);
	polConnects.append(5);

	polConnects.append(11);//bottom2
	polConnects.append(0);
	polConnects.append(4);
	polConnects.append(10);

	polConnects.append(18); //lamp1
	polConnects.append(19);
	polConnects.append(21);
	polConnects.append(20);

	polConnects.append(23);
	polConnects.append(22);
	polConnects.append(24);
	polConnects.append(25);

	polConnects.append(19);
	polConnects.append(23);
	polConnects.append(25);
	polConnects.append(21);

	polConnects.append(21);
	polConnects.append(25);
	polConnects.append(24);
	polConnects.append(20);

	polConnects.append(22);
	polConnects.append(18);
	polConnects.append(20);
	polConnects.append(24);

	polConnects.append(18);
	polConnects.append(22);
	polConnects.append(23);
	polConnects.append(19);

	polConnects.append(27); //lamp2
	polConnects.append(26);
	polConnects.append(28);
	polConnects.append(29);

	polConnects.append(30);
	polConnects.append(31);
	polConnects.append(33);
	polConnects.append(32);

	polConnects.append(31);
	polConnects.append(27);
	polConnects.append(29);
	polConnects.append(33);

	polConnects.append(33);
	polConnects.append(29);
	polConnects.append(28);
	polConnects.append(32);

	polConnects.append(26);
	polConnects.append(30);
	polConnects.append(32);
	polConnects.append(28);

	polConnects.append(30);
	polConnects.append(26);
	polConnects.append(27);
	polConnects.append(31);

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


Lamp::~Lamp()
{
}
