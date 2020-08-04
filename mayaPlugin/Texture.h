#pragma once

#include "RandomFactory.h"
#include "buildingType.h"
#include "textureType.h"

#include <string>
class Texture
{
	std::string sourceFile;
	std::string name;
	double width = 0.0;
	double height = 0.0;
	BuildingType buildingType;
	TextureType textureType;

public:
	Texture();
	Texture(std::string sourceFile);
	Texture(std::string sourceFile, TextureType textureType, BuildingType buildingType, double width, double height);
	Texture(std::string sourceFile, TextureType textureType, BuildingType buildingType);
	Texture(std::string sourceFile, double width, double height);
	~Texture();

	std::string getsourceFile();
	std::string getName();
	BuildingType getBuildingType();
	TextureType getTextureType();
	double getHeight();
	double getWidth();
	void setName(std::string name);
};

