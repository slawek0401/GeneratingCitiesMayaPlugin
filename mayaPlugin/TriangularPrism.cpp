#include "TriangularPrism.h"



TriangularPrism::TriangularPrism(double moveX, double moveY, double moveZ)
{/*
		  4---------5
		  |\        |\
		  |	3-------|-2
		  |/        |/
		  0---------1
*/
	vert.append(MFloatPoint(-1 + moveX, 0 + moveY, 1 + moveZ));  //0
	vert.append(MFloatPoint(1 + moveX, 0 + moveY, 1 + moveZ)); //1
	vert.append(MFloatPoint(1 + moveX, 0 + moveY, -1 + moveZ)); //2
	vert.append(MFloatPoint(-1 + moveX, 0 + moveY, -1 + moveZ));//3
	vert.append(MFloatPoint(-1 + moveX, 2 + moveY, 0 + moveZ)); //4
	vert.append(MFloatPoint(1 + moveX, 2 + moveY, 0 + moveZ)); //5
	

	for (int i = 0; i < 3; ++i)
		polCounts.append(4);
	for (int i = 0; i < 2; ++i)
		polCounts.append(3);

	polConnects.append(0);//bottom
	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(3);

	polConnects.append(0);//front
	polConnects.append(1);
	polConnects.append(5);
	polConnects.append(4);

	polConnects.append(2);//back
	polConnects.append(3);
	polConnects.append(4);
	polConnects.append(5);

	polConnects.append(3);//left
	polConnects.append(0);
	polConnects.append(4);

	polConnects.append(1);//right
	polConnects.append(2);
	polConnects.append(5);

	oneTextureOnWhole = false;
	std::vector<int> walls{ 3, 4 };
	std::vector<int> roof{ 1, 2 };
	texOnFaceIndexes.push_back(walls); //walls
	texOnFaceIndexes.push_back(roof); //roof

	float u[7] = {
			0.0, 20.0, 20.0, 0.0,//roof
			0.0, 2.0, 1.0,//walls
	};
	float v[7] = {
			0.0, 0.0, 20.0, 20.0,//roof
			0.0, 0.0, 2.0,//walls
	};
	int ids[18] = {
			0,0,0,0,//bottom
			0,1,2,3,//front
			0,1,2,3,//back
			4,5,6,//left
			4,5,6//right
	};
	xTexCoordsIndexFrom = 0;
	xTexCoordsIndexTo = 4;
	zTexCoordsIndexFrom = 4;
	zTexCoordsIndexTo = 7;

	for (int i = 0; i < polCounts.length(); ++i)
		UVcounts.append(polCounts[i]);
	for (int i = 0; i < polConnects.length(); ++i)
		UVids.append(ids[i]);
	for (int i = 0; i < 7; ++i)
		uArray.append(u[i]);
	for (int i = 0; i < 7; ++i)
		vArray.append(v[i]);
}


TriangularPrism::~TriangularPrism()
{
}

void TriangularPrism::assignTexture(Texture walls, Texture roof) {
	textures.push_back(walls);
	textures.push_back(roof);
}