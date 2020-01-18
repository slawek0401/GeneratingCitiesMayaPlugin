#pragma once

#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <maya\MFloatArray.h>
#include <maya\MGlobal.h>
#include <cmath>
#include <vector>

#include "Texture.h"

class Primitive
{
protected:
	int xTexCoordsIndexFrom;
	int xTexCoordsIndexTo;
	int zTexCoordsIndexFrom;
	int zTexCoordsIndexTo;
	bool oneTextureOnWhole;
	std::vector<Texture> textures;
	std::vector<std::vector<int>> texOnFaceIndexes;
	std::string nameInMaya;

public:
	MFloatPointArray vert;
	MIntArray polCounts;
	MIntArray polConnects;
	MFloatArray uArray;
	MFloatArray vArray;
	MIntArray UVids;
	MIntArray UVcounts;

	Primitive();
	~Primitive();

	void setAsCuboid(int moveX, int moveZ);
	void setAsPyramid(int moveX, int moveY, int moveZ);

	void move(double moveX, double moveY, double moveZ);
	void scale(double scaleX, double scaleY, double scaleZ);
	void scale(double scale);
	void rotateY(double degrees);
	MFloatPointArray getVert();
	MIntArray getpolCounts();
	MIntArray getpolConnects();
	MFloatArray getUArray();
	MFloatArray getVArray();
	MIntArray getUVids();
	MIntArray getUVcounts();
	void scaleXTexture(double scale);
	void scaleYTexture(double scale);
	void scaleZTexture(double scale);
	void replace(int i, float newVal, MFloatArray& array);
	void setNewScaleHeight(double height);
	void setNewHeight(double height);

	double getHeight();
	bool hasOneTextureOnWhole();
	void assignTexture(Texture tex);
	std::vector<Texture> getTextures();
	std::vector<std::vector<int>> getTexturesOnFaceIndexes();
	void setNameInMaya(std::string name);
	std::string getNameInMaya();
};

