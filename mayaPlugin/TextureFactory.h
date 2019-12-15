#pragma once

#include <vector>
#include "Texture.h"

class TextureFactory
{
	std::vector<Texture> availableTextures;

	int findIndexByFileName(std::string fileName);
public:
	TextureFactory();
	~TextureFactory();
	void load();
	void setNameToTexture(Texture tex, std::string name);

	Texture getRandomTextureByType(TextureType type);
	Texture getRandomWallTexture();
	Texture getRandomWallTextureWithSpecifiedType(BuildingType type);
	std::vector<Texture> getAllAviableWallTextures();
	std::vector<Texture> getAllAviableWallTexturesWithSpecifiedType(BuildingType type);
	Texture getRandomStreetTexture();
	std::vector<Texture> getAllAviableStreetTextures();
	std::vector<Texture> getTexturesByType(TextureType type);
	std::vector<Texture> getAllTextures();
	
};

