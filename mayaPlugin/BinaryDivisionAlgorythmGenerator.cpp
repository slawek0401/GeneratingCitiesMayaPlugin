#include "BinaryDivisionAlgorythmGenerator.h"

BinaryDivisionAlgorythmGenerator::BinaryDivisionAlgorythmGenerator(TextureFactory texFactory, unsigned divisionsNumber) {
	this->texFactory = texFactory;
	this->divisionsNumber = divisionsNumber;
}

BinaryDivisionAlgorythmGenerator::BinaryDivisionAlgorythmGenerator(TextureFactory texFactory, unsigned divisionsNumber, double xMin, double xMax, double zMin, double zMax) : BinaryDivisionAlgorythmGenerator(texFactory, divisionsNumber){
	this->xMin = xMin;
	this->xMax = xMax;
	this->zMin = zMin;
	this->zMax = zMax;
}

std::vector<Street*> BinaryDivisionAlgorythmGenerator::generate() {
	std::vector<Street*> streets;
	bool horizontal = true;
	double mi = (xMin + xMax) / 2;
	double sigma = (xMax - xMin) / 6;
	double division = randomFactory.getNormalValue(mi, sigma);
	return streets;
}