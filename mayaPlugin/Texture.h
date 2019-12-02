#pragma once

#include "RandomFactory.h"

#include <string>
class Texture
{
	std::string sourceFile;
	std::string name;
	double width;
	double height;

public:
	Texture();
	Texture(std::string sourceFile);
	Texture(std::string sourceFile, double width, double height);
	~Texture();

	std::string getsourceFile();
	std::string getName();
	void setName(std::string name);
};

