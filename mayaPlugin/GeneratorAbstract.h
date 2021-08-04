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

class GeneratorAbstract
{
	friend class FractalGenerator;
protected:
	std::vector<Point> limitPoints;
	std::vector<Point> roadsPoints;
	std::vector<Street*> streets;
	RandomFactory randomFactory;
	Point cityCenter;
	double cityDiagonal = 0;
	bool cityCenterSet = false;
	bool cityDiagonalSet = false;
	TextureFactory texFactory;
	std::vector<std::pair<Point, Point>> roadConnections;
	double streetWidth = 2;
	bool ignoreVisualObjects = false;

public:
	virtual std::vector<Street*> generate() = 0;
	void setCityCenter(Point center);
	Point getCityCenter();
	void countCityCenter();
	void setCityDiagonal(double diagonal);
	double getCityDiagonal();
	void countCityDiagonal();

protected:
	void addCrossings();
	Street* createStreet(Point p, Point q, std::vector<double> buildingsAlong);
	BuildingType getBuildingTypeByDistanceFromCentre(Point p);
	void addStreets();
	static bool comparePointAngle(const Point& a, const Point& b, const Point& middle);
	void setIgnoreVisualObjects(bool ignoreVisualObjects);
};

