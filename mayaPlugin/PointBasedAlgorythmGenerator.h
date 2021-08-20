#pragma once

#include <vector>
#include "Point.h"
#include "RandomFactory.h"
#include "TextureFactory.h"
#include "Street.h"
#include "Algorythms.h"
#include "Vector3.h"
#include "Polygon.h"
#include "FastNoiseLite.h"
#include "GeneratorAbstract.h"

class PointBasedAlgorythmGenerator : public GeneratorAbstract
{
//protected:
//	std::vector<Point> limitPoints;
//	std::vector<Point> roadsPoints;
//	std::vector<Street*> streets;
	unsigned pointNumber;
	unsigned undeletableRoadConnectionIndex = 0;
	std::string type = "minDist";
//	RandomFactory randomFactory;
//	Point cityCenter;
//	double cityDiagonal = 0;
//	bool cityCenterSet = false;
//	bool cityDiagonalSet = false;
//	TextureFactory texFactory;
//	std::vector<std::pair<Point, Point>> roadConnections;
//	double streetWidth = 2;
	

	// mo¿na losowaæ w zakresie od maksa do minimum góra-dó³, dla wylosowanej liczby szukac na prawo i na lewo najblizszych punktów, wyliczac z liniowej jak ie jest ograniczenie prawo-lewo
public:
	PointBasedAlgorythmGenerator() {};
	PointBasedAlgorythmGenerator(TextureFactory texFactory, unsigned pointNumber);
	PointBasedAlgorythmGenerator(TextureFactory texFactory, unsigned pointNumber, double xMin, double xMax, double zMin, double zMax);
	std::vector<Street*> generate();
	void setUndeletableRoadConnectionIndex(unsigned);
	void setType(std::string type);

protected:
	void randomPoints();
	void randomMinDistPoints(double minDist, unsigned maxMistakes);
	void randomFastNoicePoints();
	void findRoadConnections(double minLength=10, double maxLength=30);
	std::vector<double> findXLimits(double z);
	void deleteRoadsIntersections();
	void deleteSmallAngleRoads();
	bool canBeDeleted(unsigned roadConnectionId);
};

