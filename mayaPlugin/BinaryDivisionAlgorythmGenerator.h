#pragma once

#include <set>

#include "TextureFactory.h"
#include "Street.h"
#include "PointBasedAlgorythmGenerator.h"
#include "Boundaries.h"

class BinaryDivisionAlgorythmGenerator : private PointBasedAlgorythmGenerator
{
private:
	unsigned divisionsNumber;
	double xMin, xMax, zMin, zMax;
	/*TextureFactory texFactory;
	RandomFactory randomFactory;
	std::vector<Point> roadsPoints;
	std::vector<Street*> streets;
	Point cityCenter;
	double cityDiagonal = 0;
	std::vector<std::pair<Point, Point>> roadConnections;
	double streetWidth = 2;*/

public:
	BinaryDivisionAlgorythmGenerator() {};
	BinaryDivisionAlgorythmGenerator(TextureFactory texFactory, unsigned divisionsNumber);
	BinaryDivisionAlgorythmGenerator(TextureFactory texFactory, unsigned divisionsNumber, double xMin, double xMax, double zMin, double zMax);
	std::vector<Street*> generate();
private:
	unsigned divideRoadConnetion(unsigned connectionId, double division, bool horizontal);
	Boundaries generateRecursive(unsigned iter, Boundaries& bound, bool horizontal);
	void findPointsWithRoadConnections();
	unsigned findLeftId(Boundaries bound, double division);
	unsigned findTopId(Boundaries bound, double division);
	unsigned findRightId(Boundaries bound, double division);
	unsigned findDownId(Boundaries bound, double division);
	unsigned findConnectionId(std::vector<unsigned> ids, double division, double (*getParam)(Point));
};

