#pragma once

#include "Building.h"
#include "Street.h"
#include "TextureFactory.h"
#include "RandomFactory.h"
#include "Cuboid.h"
#include "TriangularPrism.h"
#include "Pyramid.h"
#include "Plane.h"

class BuildingsFactory
{
private:
	static Building* setRandomHeight(Building* building);
	static Primitive* setRandomHeight(Primitive* prim, double ratio);
	static Building* setRandomWidth(Building* building);
	static void addWindow(TextureFactory texFactory, Building* b, double scaleX, double scaleY, double scaleZ, double moveX, double moveY, double moveZ, double rotateY=0);

public:
	BuildingsFactory();
	~BuildingsFactory();

	static Building* createRandomTypeBuilding(TextureFactory texFactory);
	static Building* createSpecifiedTypeBuilding(BuildingType type, TextureFactory texFactory);
	static Building* createHouse(TextureFactory texFactory);
	static Building* createSkyscraper(TextureFactory texFactory);
	static Building* createTenement(TextureFactory texFactory);
	static Building* createBlock(TextureFactory texFactory);
};

