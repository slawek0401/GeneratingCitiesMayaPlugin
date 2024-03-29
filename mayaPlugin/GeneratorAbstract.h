#pragma once

#include <vector>
#include "Point.h"
#include "RandomFactory.h"
#include "TextureFactory.h"
#include "Street.h"
#include "Bridge.h"
#include "Algorythms.h"
#include "Vector3.h"
#include "Polygon.h"
#include "FastNoiseLite.h"
#include "GeneratorAbstract.h"
#include "RoadConnection.h"

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
	std::vector<RoadConnection> roadConnections;
	double streetWidth = 2;
	bool ignoreVisualObjects = false;

public:
	virtual std::vector<Street*> generate() = 0;
	void setCityCenter(Point center);
	void setStreetWidth(double width);
	Point getCityCenter();
	void countCityCenter();
	void setCityDiagonal(double diagonal);
	double getCityDiagonal();
	void countCityDiagonal();

protected:
	void setStreetVisualProperies(Street* street, std::vector<double> buildingsAlong, bool setBuildings, Point p, Point q, double streetLength, Texture strTex, Texture walkTex);
	void addCrossings();
	std::vector<Street*> createStreet(RoadConnection rc, std::vector<double> buildingsAlong);
	BuildingType getBuildingTypeByDistanceFromCentre(Point p);
	void addStreets();
	static bool comparePointAngle(const Point& a, const Point& b, const Point& middle);
	void setIgnoreVisualObjects(bool ignoreVisualObjects);
};

