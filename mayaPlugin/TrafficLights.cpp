#include "TrafficLights.h"

TrafficLights::TrafficLights(double moveX, double moveZ) {
	vert.append(MFloatPoint(0.01 + moveX, 1, 0.01 + moveZ));  //0
	vert.append(MFloatPoint(-0.01 + moveX, 1, 0.01 + moveZ)); //1
	vert.append(MFloatPoint(-0.01 + moveX, 0, 0.01 + moveZ)); //2
	vert.append(MFloatPoint(0.01 + moveX, 0, 0.01 + moveZ));  //3
	vert.append(MFloatPoint(0.01 + moveX, 1, -0.01 + moveZ)); //4
	vert.append(MFloatPoint(-0.01 + moveX, 1, -0.01 + moveZ)); //5
	vert.append(MFloatPoint(-0.01 + moveX, 0, -0.01 + moveZ)); //6
	vert.append(MFloatPoint(0.01 + moveX, 0, -0.01 + moveZ)); //7

	vert.append(MFloatPoint(0.01 + moveX, 0.9, -0.01 + moveZ)); //8
	vert.append(MFloatPoint(0.01 + moveX, 0.9, 0.01 + moveZ)); //9
	vert.append(MFloatPoint(0.01 + moveX, 0.91, 0.01 + moveZ)); //10
	vert.append(MFloatPoint(0.01 + moveX, 0.91, -0.01 + moveZ)); //11

	vert.append(MFloatPoint(0.5 + moveX, 1.0, -0.01 + moveZ)); //12
	vert.append(MFloatPoint(0.5 + moveX, 1.0, 0.01 + moveZ)); //13
	vert.append(MFloatPoint(0.5 + moveX, 1.01, 0.01 + moveZ)); //14
	vert.append(MFloatPoint(0.5 + moveX, 1.01, -0.01 + moveZ)); //15

	vert.append(MFloatPoint(0.55 + moveX, 0.9, 0.02 + moveZ)); //16
	vert.append(MFloatPoint(0.45 + moveX, 0.9, 0.02 + moveZ)); //17
	vert.append(MFloatPoint(0.48 + moveX, 0.95, 0.01 + moveZ)); //18
	vert.append(MFloatPoint(0.52 + moveX, 0.95, 0.01 + moveZ)); //19

	vert.append(MFloatPoint(0.55 + moveX, 1.1, 0.02 + moveZ)); //20
	vert.append(MFloatPoint(0.45 + moveX, 1.1, 0.02 + moveZ)); //21
	vert.append(MFloatPoint(0.48 + moveX, 1.05, 0.01 + moveZ)); //22
	vert.append(MFloatPoint(0.52 + moveX, 1.05, 0.01 + moveZ)); //23


	for (int i = 0; i < 18; ++i)
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

	polConnects.append(8); //czeœæ ukoœna
	polConnects.append(9);
	polConnects.append(10);
	polConnects.append(11);

	polConnects.append(15);
	polConnects.append(14);
	polConnects.append(13);
	polConnects.append(12);

	polConnects.append(9);
	polConnects.append(13);
	polConnects.append(14);
	polConnects.append(10);

	polConnects.append(10);
	polConnects.append(14);
	polConnects.append(15);
	polConnects.append(11);

	polConnects.append(12);
	polConnects.append(8);
	polConnects.append(11);
	polConnects.append(15);

	polConnects.append(8);
	polConnects.append(12);
	polConnects.append(13);
	polConnects.append(9);

	polConnects.append(17);//sygnalizator przód
	polConnects.append(16);
	polConnects.append(20);
	polConnects.append(21);

	polConnects.append(21); // góra
	polConnects.append(20);
	polConnects.append(23);
	polConnects.append(22);

	polConnects.append(16); //prawa
	polConnects.append(19);
	polConnects.append(23);
	polConnects.append(20);

	polConnects.append(18);//lewa
	polConnects.append(17);
	polConnects.append(21);
	polConnects.append(22);

	polConnects.append(19); //tyl
	polConnects.append(18);
	polConnects.append(22);
	polConnects.append(23);

	polConnects.append(18); //dol
	polConnects.append(19);
	polConnects.append(16);
	polConnects.append(17);

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

TrafficLights::~TrafficLights() {

}