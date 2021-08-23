#include "Bridge.h"

Bridge::Bridge(double walkPathFrac, double x1, double z1, double width, double length, double height, double uprise) {
	this->width = width;
	this->length = length;
	this->walkPathFrac = walkPathFrac;

	/*
	0-8---15-7
	| |   |  |
	| |   |  |
	1-9   14-6
	| |   |  |
	| |   |  |
	| |   |  |
	2-10  13-5
	| |   |  |
	| |   |  |
	3-11--12-4
	*/
	vert.append(MFloatPoint(x1, 0, z1)); //0
	vert.append(MFloatPoint(x1, height, z1 + uprise)); //1
	vert.append(MFloatPoint(x1, height, z1 + length - uprise)); //2
	vert.append(MFloatPoint(x1, 0, z1 + length)); //3

	vert.append(MFloatPoint(x1 + width, 0, z1 + length)); //4
	vert.append(MFloatPoint(x1 + width, height, z1 + length - uprise)); //5
	vert.append(MFloatPoint(x1 + width, height, z1 + uprise)); //6
	vert.append(MFloatPoint(x1 + width, 0, z1)); //7

	vert.append(MFloatPoint(x1 + walkPathFrac * width, 0, z1)); //8
	vert.append(MFloatPoint(x1 + walkPathFrac * width, height, z1 + uprise)); //9
	vert.append(MFloatPoint(x1 + walkPathFrac * width, height, z1 + length - uprise)); //10
	vert.append(MFloatPoint(x1 + walkPathFrac * width, 0, z1 + length)); //11

	vert.append(MFloatPoint(x1 + (1 - walkPathFrac) * width, 0, z1 + length)); //12
	vert.append(MFloatPoint(x1 + (1 - walkPathFrac) * width, height, z1 + length - uprise)); //13
	vert.append(MFloatPoint(x1 + (1 - walkPathFrac) * width, height, z1 + uprise)); //14
	vert.append(MFloatPoint(x1 + (1 - walkPathFrac) * width, 0, z1)); //15

	for (int i = 0; i < 9; ++i)
		polCounts.append(4);

	polConnects.append(0); //chodnik
	polConnects.append(1);
	polConnects.append(9);
	polConnects.append(8);
	
	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(10);
	polConnects.append(9);

	polConnects.append(2);
	polConnects.append(3);
	polConnects.append(11);
	polConnects.append(10);

	polConnects.append(8); //jezdnia
	polConnects.append(9);
	polConnects.append(14);
	polConnects.append(15);
	
	polConnects.append(9);
	polConnects.append(10);
	polConnects.append(13);
	polConnects.append(14);
	
	polConnects.append(10);
	polConnects.append(11);
	polConnects.append(12);
	polConnects.append(13);

	polConnects.append(15); //chodnik
	polConnects.append(14);
	polConnects.append(6);
	polConnects.append(7);

	polConnects.append(14);
	polConnects.append(13);
	polConnects.append(5);
	polConnects.append(6);

	polConnects.append(13);
	polConnects.append(12);
	polConnects.append(4);
	polConnects.append(5);

	oneTextureOnWhole = false;
	std::vector<int> walkPaths{ 0, 1, 2, 6, 7, 8  };
	std::vector<int> road{ 3, 4, 5 };
	texOnFaceIndexes.push_back(walkPaths);
	texOnFaceIndexes.push_back(road);

	float u[] = {
			0.0, 1.0, 1.0, 0.0,
			0.0, 1.0, 1.0, 0.0,
			0.0, 1.0, 1.0, 0.0
	};
	float v[] = {
			0.0, 0.0, uprise * 2, uprise * 2,
			0.0, 0.0, (length - 2 * uprise) * 2, (length - 2 * uprise) * 2,
			0.0, 0.0, uprise * 2, uprise * 2
	};
	int ids[] = {
			0,3,2,1,
			4,7,6,5,
			8,11,10,9
	};
	for (int i = 0; i < 9; ++i)
		UVcounts.append(4);
	for (int i = 0; i < 36; ++i)
		UVids.append(ids[i % 12]);
	for (int i = 0; i < 12; ++i)
		uArray.append(u[i]);
	for (int i = 0; i < 12; ++i)
		vArray.append(v[i]);
}