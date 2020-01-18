#pragma once

#include "RandomFactory.h"
#include "buildingType.h"
#include "textureType.h"

#include <string>
class Texture
{
	std::string sourceFile;
	std::string name;
	double width;
	double height;
	BuildingType buildingType;
	TextureType textureType;

public:
	Texture();
	Texture(std::string sourceFile);
	Texture(std::string sourceFile, TextureType textureType, BuildingType buildingType);
	Texture(std::string sourceFile, double width, double height);
	~Texture();

	std::string getsourceFile();
	std::string getName();
	BuildingType getBuildingType();
	TextureType getTextureType();
	void setName(std::string name);
};

