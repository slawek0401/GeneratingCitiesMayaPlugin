#include "TextureFactory.h"
#include <maya/MGlobal.h>


TextureFactory::TextureFactory()
{
	load();
}


TextureFactory::~TextureFactory()
{
}

void TextureFactory::load() {
	std::string folders[] = {
		"blok",
		"chodnik",
		"dach",
		"dom_jednorodzinny",
		"jezdnia",
		"kamienica",
		"wiezowiec"
	};
	unsigned counts[] = {4,0,10,3,3,6,9};
	TextureType textureTypes[] = { sciana, chodnik, dach, sciana, jezdnia, sciana, sciana };
	BuildingType buildingTypes[] = {blok, undefined, undefined, dom_jednorodzinny, undefined, kamienica, wiezowiec };
	
	std::string nameBase = "tex";
	for (int i = 0; i < 7; ++i) 
		for (int j = 1; j <= counts[i]; ++j) {
			Texture tex(folders[i] + "\\\\" + nameBase + std::to_string(j), textureTypes[i], buildingTypes[i]);
			availableTextures.push_back(tex);
		}
}

Texture TextureFactory::getRandomTextureByType(TextureType type) {
	auto availableTypeTextures = getTexturesByType(type);
	static RandomFactory rand;
	int index = rand.getLinearValue(0, availableTypeTextures.size() - 1);
	return availableTypeTextures[index];
}

Texture TextureFactory::getRandomWallTexture() {
	auto availableWallsTextures = getAllAviableWallTextures();
	static RandomFactory rand;
	int index = rand.getLinearValue(0, availableWallsTextures.size()-1);
	return availableWallsTextures[index];
}

Texture TextureFactory::getRandomWallTextureWithSpecifiedType(BuildingType type) {
	auto availableWallsTextures = getAllAviableWallTexturesWithSpecifiedType(type);
	static RandomFactory rand;
	int index = rand.getLinearValue(0, availableWallsTextures.size() - 1);
	return availableWallsTextures[index];
}

std::vector<Texture> TextureFactory::getAllAviableWallTextures() {
	return getTexturesByType(sciana);
}

std::vector<Texture> TextureFactory::getAllAviableWallTexturesWithSpecifiedType(BuildingType type) {
	std::vector<Texture> res;
	for (auto tex : getAllAviableWallTextures())
		if (tex.getBuildingType() == type)
			res.push_back(tex);
	return res;
}

Texture TextureFactory::getRandomStreetTexture() {
	auto availableStreetTextures = getAllAviableStreetTextures();
	static RandomFactory rand;
	int index = rand.getLinearValue(0, availableStreetTextures.size() - 1);
	return availableStreetTextures[index];
}

std::vector<Texture> TextureFactory::getAllAviableStreetTextures() {
	return getTexturesByType(jezdnia);
}

std::vector<Texture> TextureFactory::getTexturesByType(TextureType type) {
	std::vector<Texture> res;
	for (auto tex : availableTextures)
		if (tex.getTextureType() == type)
			res.push_back(tex);
	return res;
}

void TextureFactory::setNameToTexture(Texture tex, std::string name) {
	int i = findIndexByFileName(tex.getsourceFile());
	availableTextures[i].setName(name);
}

int TextureFactory::findIndexByFileName(std::string fileName) {
	for (int i = 0; i < availableTextures.size(); ++i) 
		if (availableTextures[i].getsourceFile() == fileName)
			return i;
	
	return -1;
}

std::vector<Texture> TextureFactory::getAllTextures() {
	return availableTextures;
}