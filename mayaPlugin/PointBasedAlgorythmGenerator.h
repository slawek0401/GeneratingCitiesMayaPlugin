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

class PointBasedAlgorythmGenerator
{
protected:
	std::vector<Point> limitPoints;
	std::vector<Point> roadsPoints;
	std::vector<Street*> streets;
	unsigned pointNumber;
	RandomFactory randomFactory;
	Point cityCenter;
	double cityDiagonal = 0;
	bool cityCenterSet = false;
	bool cityDiagonalSet = false;
	TextureFactory texFactory;
	std::vector<std::pair<Point, Point>> roadConnections;
	double streetWidth = 2;
	

	// mo¿na losowaæ w zakresie od maksa do minimum góra-dó³, dla wylosowanej liczby szukac na prawo i na lewo najblizszych punktów, wyliczac z liniowej jak ie jest ograniczenie prawo-lewo
public:
	PointBasedAlgorythmGenerator() {};
	PointBasedAlgorythmGenerator(TextureFactory texFactory, unsigned pointNumber);
	PointBasedAlgorythmGenerator(TextureFactory texFactory, unsigned pointNumber, double xMin, double xMax, double zMin, double zMax);
	void setCityCenter(Point center);
	Point getCityCenter();
	void countCityCenter();
	void setCityDiagonal(double diagonal);
	double getCityDiagonal();
	void countCityDiagonal();
	std::vector<Street*> generate();

protected:
	void randomPoints();
	void randomMinDistPoints(double minDist, unsigned maxMistakes);
	void randomFastNoicePoints();
	void findRoadConnections(double minLength=4, double maxLength=20);
	void addCrossings();
	Street* createStreet(Point p, Point q, std::vector<double> buildingsAlong);
	std::vector<double> findXLimits(double z);
	BuildingType getBuildingTypeByDistanceFromCentre(Point p);
	double countDistance(Point p, Point q);
	double pow2(double a);
	static bool comparePointAngle(const Point &a, const Point &b, const Point &middle);
	void deleteRoadsIntersections();
	void deleteSmallAngleRoads();
	void addStreets();
	
};

