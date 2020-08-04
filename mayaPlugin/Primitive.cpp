#include "Primitive.h"
#include <string>
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
	xTexCoordsIndexTo = 5;
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

void Primitive::setAsPyramid(int moveX, int moveY, int moveZ)
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
	float u[8] = {
			0.0, 2.0, 1.0,
			0.0, 2.0, 1.0
	};
	float v[8] = {
			0.0, 0.0, 2.0,
			0.0, 0.0, 2.0
	};
	int ids[24] = {
			0,0,0,0,//bottom
			0,1,2,//front
			0,1,2,//back
			3,4,5,//left
			3,4,5//right
	};
	xTexCoordsIndexFrom = 0;
	xTexCoordsIndexTo = 4;
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

void Primitive::move(double moveX, double moveY, double moveZ) {
	for (int i = 0; i < vert.length(); ++i) {
		vert[i].x += moveX;
		vert[i].y += moveY;
		vert[i].z += moveZ;
	}
}

void Primitive::scale(double scaleX, double scaleY, double scaleZ) {
	for (int i = 0; i < vert.length(); ++i) {
		if (scaleX != 1) 
			vert[i].x *= scaleX;
		if (scaleY != 1) 
			vert[i].y *= scaleY;
		if (scaleZ != 1) 
			vert[i].z *= scaleZ;
	}
	if (scaleX != 1) 
		scaleXTexture(scaleX);
	if (scaleY != 1) 
		scaleYTexture(scaleY);
	if (scaleZ != 1)
		scaleZTexture(scaleZ);
}

void Primitive::scaleXTexture(double scale) {
	for (int i = xTexCoordsIndexFrom; i < xTexCoordsIndexTo; ++i) {
		float newVal = round(uArray[i] * scale);
		if (newVal == 0)
			newVal = 1;
		if (uArray[i] > 0)
			replace(i, newVal, uArray);
	}
}

void Primitive::scaleZTexture(double scale) {
	for (int i = zTexCoordsIndexFrom; i < zTexCoordsIndexTo; ++i) {
		float newVal = round(uArray[i] * scale);
		if (newVal == 0)
			newVal = 1;
		if (uArray[i] > 0)
			replace(i, newVal, uArray);
	}
}
void Primitive::scaleYTexture(double scale) {
	for (int i = 0; i < vArray.length(); ++i) {
		float newVal = round(vArray[i] * scale);
		if (newVal == 0)
			newVal = 1;
		if (vArray[i] > 0)
			replace(i, newVal, vArray);
	}
}

void Primitive::replace(int i, float newVal, MFloatArray& array){
	array.remove(i);
	array.insert(newVal, i);
}

void Primitive::scale(double scale) {
	if (scale != 1)
		this->scale(scale, scale, scale);
}

void Primitive::rotateY(double degrees) {
	double degInRad = degrees * M_PI / 180;
	for (int i = 0; i < vert.length(); ++i) {
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

void Primitive::setNewScaleHeight(double height) {
	double newHeight = ceil(5 * height);
	setNewHeight(newHeight);
}

void Primitive::setNewHeight(double height) {
	double newHeight = ceil(height);
	for (int i = 0; i < vert.length(); ++i)
		if (vert[i].y > 0)
			vert[i].y = newHeight;
	for (int i = 0; i < vArray.length(); ++i)
		if (vArray[i] > 0)
			replace(i, newHeight, vArray);
}

double Primitive::getHeight() {
	double maxHeight = 0.0;
	for (auto x : vert) {
		double currHeight = x.y;
		if (maxHeight < currHeight)
			maxHeight = currHeight;
	}
	return maxHeight;
}

bool Primitive::hasOneTextureOnWhole() {
	return oneTextureOnWhole;
}
void Primitive::assignTexture(Texture tex) {
	if (tex.getHeight() > 0 && tex.getWidth() > 0) {
		scaleXTexture(tex.getWidth());
		scaleZTexture(tex.getWidth());
		scaleYTexture(tex.getHeight());
	}
	textures.push_back(tex);
}

std::vector<Texture> Primitive::getTextures() {
	return textures;
}

std::vector<std::vector<int>> Primitive::getTexturesOnFaceIndexes(){
	return texOnFaceIndexes;
}

void Primitive::setNameInMaya(std::string name) {
	this->nameInMaya = name;
}

std::string Primitive::getNameInMaya() {
	return nameInMaya;
}