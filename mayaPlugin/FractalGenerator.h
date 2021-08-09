#pragma once

#include "GeneratorAbstract.h"
#include <map>

//??? mo¿e robiæ obs³uge ka¿dego generatora osobno, a nie razem
//
//³¹czenie prostopad³ego i point based mo¿e w taki sposób, ¿e póŸniej doci¹gaæ z point based do prostopad³ego pojedyncze drogi
//w binary division jest wyznaczanei po prostu prostok¹ta otaczaj¹cego, a póŸniej jest usuwanie przeciêæ
class mapParam {
public:
	bool foundOnLeft = false;
	bool foundOnRight = false;
	mapParam() {}
	mapParam(const mapParam& other) {
		this->foundOnLeft = other.foundOnLeft;
		this->foundOnRight = other.foundOnRight;
	}
};

class FractalGenerator : public GeneratorAbstract
{
protected:
	bool isFirstAlg = true;
	bool isMapInitialized = false;
	std::map<unsigned, mapParam> roadBoundariesMap;

protected:
	std::vector<std::vector<Point>> countNewLimitPoints();
	std::vector<unsigned> findPointsConnections(Point p);
	unsigned findAnotherConnectionId(unsigned i, Point p, bool left = false);
	std::map<unsigned, mapParam> initializeMap();

public:
	FractalGenerator() {};
	FractalGenerator(TextureFactory texFactory, double xMin, double xMax, double zMin, double zMax);
	std::vector<Street*> generate();
	FractalGenerator& addGenerator(GeneratorAbstract& genetator);
};

