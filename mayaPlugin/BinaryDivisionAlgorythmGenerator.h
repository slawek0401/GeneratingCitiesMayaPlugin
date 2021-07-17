#pragma once

#include "TextureFactory.h"
#include "Street.h"

class BinaryDivisionAlgorythmGenerator
{
private:
	TextureFactory texFactory;
	RandomFactory randomFactory;
	unsigned divisionsNumber;
	double xMin, xMax, zMin, zMax;

public:
	BinaryDivisionAlgorythmGenerator() {};
	BinaryDivisionAlgorythmGenerator(TextureFactory texFactory, unsigned divisionsNumber);
	BinaryDivisionAlgorythmGenerator(TextureFactory texFactory, unsigned divisionsNumber, double xMin, double xMax, double zMin, double zMax);
	std::vector<Street*> generate();
};

