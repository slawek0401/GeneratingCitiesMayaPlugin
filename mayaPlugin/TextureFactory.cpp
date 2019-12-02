#include "TextureFactory.h"



TextureFactory::TextureFactory()
{
	load();
}


TextureFactory::~TextureFactory()
{
}

void TextureFactory::load() {
	std::string nameBase = "tex";
	for (int i = 1; i <= 22; ++i) {
		Texture tex(nameBase + std::to_string(i));
		availableWallsTextures.push_back(tex);
	}

	nameBase = "street";
	for (int i = 1; i <= 3; ++i) {
		Texture tex(nameBase + std::to_string(i));
		availableStreetTextures.push_back(tex);
	}
}

Texture TextureFactory::getRandomWallTexture() {
	static RandomFactory rand;
	int index = rand.getLinearValue(0, availableWallsTextures.size()-1);
	return availableWallsTextures[index];
}

std::vector<Texture>* TextureFactory::getAllAviableWallTextures() {
	return &(this->availableWallsTextures);
}

Texture TextureFactory::getWallTextureByIndex(size_t index) {
	return this->availableWallsTextures[index];
}

Texture TextureFactory::getRandomStreetTexture() {
	static RandomFactory rand;
	int index = rand.getLinearValue(0, availableStreetTextures.size() - 1);
	return availableStreetTextures[index];
}

std::vector<Texture>* TextureFactory::getAllAviableStreetTextures() {
	return &(this->availableStreetTextures);
}

Texture TextureFactory::getStreetTextureByIndex(size_t index) {
	return this->availableStreetTextures[index];
}