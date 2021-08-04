#pragma once

#include "GeneratorAbstract.h"
#include <map>

// !!! DOROBI� SZUKANIE OBWODKI I USTAWIANIE MAPY ODPOWIEDNIE !!!
//??? mo�e robi� obs�uge ka�dego generatora osobno, a nie razem
//
//��czenie prostopad�ego i point based mo�e w taki spos�b, �e p�niej doci�ga� z point based do prostopad�ego pojedyncze drogi
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

