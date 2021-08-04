#pragma once

#include "GeneratorAbstract.h"
#include <map>

// !!! DOROBIÆ SZUKANIE OBWODKI I USTAWIANIE MAPY ODPOWIEDNIE !!!
//??? mo¿e robiæ obs³uge ka¿dego generatora osobno, a nie razem
//
//³¹czenie prostopad³ego i point based mo¿e w taki sposób, ¿e póŸniej doci¹gaæ z point based do prostopad³ego pojedyncze drogi
class FractalGenerator : public GeneratorAbstract
{
protected:
	bool isFirstAlg = true;
	std::vector<std::vector<Point>> countNewLimitPoints();
	std::vector<unsigned> findPointsConnections(Point p);
	unsigned findAnotherConnectionId(unsigned i, Point p);

public:
	FractalGenerator() {};
	FractalGenerator(TextureFactory texFactory, double xMin, double xMax, double zMin, double zMax);
	std::vector<Street*> generate();
	FractalGenerator& addGenerator(GeneratorAbstract& genetator);
};

