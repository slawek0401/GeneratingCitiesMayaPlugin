#pragma once

#include "GeneratorAbstract.h"
#include <map>

//??? mo�e robi� obs�uge ka�dego generatora osobno, a nie razem
//
//��czenie prostopad�ego i point based mo�e w taki spos�b, �e p�niej doci�ga� z point based do prostopad�ego pojedyncze drogi
//w binary division jest wyznaczanei po prostu prostok�ta otaczaj�cego, a p�niej jest usuwanie przeci��
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

