#pragma once

#include <vector>
#include "Texture.h"

class TextureFactory
{
	std::vector<Texture> availableWallsTextures;
	std::vector<Texture> availableStreetTextures;
public:
	TextureFactory();
	~TextureFactory();
	void load();
	Texture getRandomWallTexture();
	Texture getWallTextureByIndex(size_t index);
	std::vector<Texture>* getAllAviableWallTextures(); //zwracana jest kopia, a nie powinna, chcemy referencje

	Texture getRandomStreetTexture();
	Texture getStreetTextureByIndex(size_t index);
	std::vector<Texture>* getAllAviableStreetTextures();
};

