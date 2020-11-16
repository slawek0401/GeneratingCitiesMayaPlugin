#include "TextureFactory.h"
#include <maya/MGlobal.h>
#include <iostream>
#include <filesystem>
#include <direct.h>

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
		"wiezowiec",
		"trawa",
		"asfalt",
		"okno",
		"metal"
	};
	unsigned counts[] = {4,4,10,6,3,6,9,3,2,1,1};
	TextureType textureTypes[] = { sciana, chodnik, dach, sciana, jezdnia, sciana, sciana, trawa, asfalt, okno, metal };
	BuildingType buildingTypes[] = {blok, undefined, undefined, dom_jednorodzinny, undefined, kamienica, wiezowiec, undefined, undefined, undefined, undefined };
	std::string nameBase = "tex"; 
	std::string direcotry = "C:\\Users\\Slawek\\Documents\\git_repo\\GeneratingCitiesMayaPlugin\\x64\\Debug\\"; // this source path has to be eventually passed by user, it points to texture directories
		for (int i = 0; i < sizeof counts / sizeof counts[0]; ++i) { //9
			std::ifstream file;
			file.open(direcotry + folders[i] + "\\config.txt");
			MGlobal::displayInfo(MString((folders[i] + "\\config.txt").data()));
			if (file.is_open()) {
				
				for (int j = 1; j <= counts[i]; ++j) {
					double width, height;
					auto name = getName(file);
					file >> width >> height;
					ignoreOneCharacter(file);
					MGlobal::displayInfo(MString((name + " " + std::to_string(width) + " " + std::to_string(height)).data()));
					Texture tex(folders[i] + "\\\\" + name, textureTypes[i], buildingTypes[i], 1/width, 1/height);
					availableTextures.push_back(tex);
					
				}
				file.close();
			}
			else {

				for (int j = 1; j <= counts[i]; ++j) {
					
					Texture tex(folders[i] + "\\\\" + nameBase + std::to_string(j), textureTypes[i], buildingTypes[i]);
					availableTextures.push_back(tex);
				}
			}
		}
}

void TextureFactory::ignoreOneCharacter(std::ifstream& file) {
	char c;
	file.get(c);
}

std::string TextureFactory::getName(std::ifstream &file) {
	std::string res = "";
	char c;
	while (file.get(c) && c != ' ')
		res.push_back(c);
	return res;
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