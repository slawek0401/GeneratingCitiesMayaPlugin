#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(std::string sourceFile)
{
	this->sourceFile = sourceFile;
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

void Texture::setName(std::string name) {
	this->name = name;
}