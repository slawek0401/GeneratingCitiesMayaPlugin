#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(std::string sourceFile)
{
	this->sourceFile = sourceFile;
}

Texture::Texture(std::string sourceFile, TextureType textureType, BuildingType buildingType, double width, double height) {
	this->sourceFile = sourceFile;
	this->textureType = textureType;
	this->buildingType = buildingType;
	this->height = height;
	this->width = width;
}

Texture::Texture(std::string sourceFile, TextureType textureType, BuildingType buildingType) {
	this->sourceFile = sourceFile;
	this->textureType = textureType;
	this->buildingType = buildingType;
}

Texture::Texture(std::string sourceFile, double width, double height)
{
	this->sourceFile = sourceFile;
	this->height = height;
	this->width = width;
}

Texture::~Texture()
{
}

std::string Texture::getsourceFile() {
	return sourceFile;
}

std::string Texture::getName() {
	return name;
}

BuildingType Texture::getBuildingType() {
	return this->buildingType;
}

TextureType Texture::getTextureType() {
	return this->textureType;
}


double Texture::getHeight() {
	return height;
}

double Texture::getWidth() {
	return width;
}

void Texture::setName(std::string name) {
	this->name = name;
}