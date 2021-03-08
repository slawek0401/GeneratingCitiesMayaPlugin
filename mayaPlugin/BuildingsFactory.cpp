#include "BuildingsFactory.h"

BuildingsFactory::BuildingsFactory()
{
}

BuildingsFactory::~BuildingsFactory()
{
}

Building* BuildingsFactory::createRandomTypeBuilding(TextureFactory texFactory) {
	static RandomFactory rand;
	return createSpecifiedTypeBuilding((BuildingType)rand.getLinearValue(0,3), texFactory);
	//return createSpecifiedTypeBuilding(BuildingType::dom_jednorodzinny, texFactory);
}

Building* BuildingsFactory::createSpecifiedTypeBuilding(BuildingType type, TextureFactory texFactory) {
	switch (type) {
	case dom_jednorodzinny:
		return createHouse(texFactory);
	case wiezowiec:
		return createSkyscraper(texFactory);
	case kamienica:
		return createTenement(texFactory);
	case blok:
		return createBlock(texFactory);
	default:
		MGlobal::displayInfo("type of building in BuildingFactory unrecognized or forbidden");
		throw std::exception("type of building in BuildingFactory unrecognized or forbidden");
	}
}

void BuildingsFactory::addWindow(TextureFactory texFactory, Building* b, double scaleX, double scaleY, double scaleZ, double moveX, double moveY, double moveZ, double rotateY) {
	Primitive* window = new Plane(-1, 0, 2, 5);
	window->rotateX(-90);
	window->rotateY(rotateY);
	window->scale(scaleX, scaleY, scaleZ);
	window->move(moveX, moveY, moveZ);
	window->scaleYTexture(0.5);
	window->scaleXTexture(0.25);
	auto windowTexture = texFactory.getRandomTextureByType(TextureType::okno);
	window->assignTexture(windowTexture);
	b->addPrimitive(window);
}

Building* BuildingsFactory::createHouse(TextureFactory texFactory) {
	static RandomFactory rand;
	Building* b = new Building();
	Primitive* prim = new Cuboid(0, 0);
	Texture wallTexture = texFactory.getRandomWallTextureWithSpecifiedType(BuildingType::dom_jednorodzinny);
	prim->setNewHeight(rand.getLinearValue(1, 2));
	prim->assignTexture(wallTexture);
	b->addMainPrimitive(prim);
	Primitive* roof;
	double buildingHeight = b->getHeight();
	if (rand.getLinearValue(0, 1) == 0) {
		roof = new Pyramid(0, buildingHeight, 0);
		roof->assignTexture(texFactory.getRandomTextureByType(dach));
	}
	else {
		roof = new TriangularPrism(0, buildingHeight, 0);
		((TriangularPrism*)roof)->assignTexture(wallTexture, texFactory.getRandomTextureByType(dach));
	}
	b->addPrimitive(roof);
	setRandomWidth(b);
	for (int i = 0; i < buildingHeight; ++i) {
		for (int j = 0; j < (int)b->frontWidth(); ++j) {
			addWindow(texFactory, b, 0.4, 0.15, 0.0001, //front
				(double)j + 0.45 - b->frontWidth() / 2 + (b->frontWidth() - floor(b->frontWidth())) / (floor(b->frontWidth() + 1)), //move x
				(double)i + 0.2, //move y
				-1.001 //move z
				);
			addWindow(texFactory, b, 0.4, 0.15, 0.0001, //rear
				(double)j + 0.45 - b->frontWidth() / 2 + (b->frontWidth() - floor(b->frontWidth())) / (floor(b->frontWidth() + 1)), //move x
				(double)i + 0.2, //move y
				1.001, //move z
				180);
		}

		for (int j = 0; j < 2; ++j) {
			addWindow(texFactory, b, 0.0001, 0.15, 0.4, //left
				-(b->frontWidth() / 2 + 0.001), //move x
				(double)i + 0.2, //move y
				(double)j + 0.45 - 1,  //move z
				-90);
			addWindow(texFactory, b, 0.0001, 0.15, 0.4, //right
				b->frontWidth() / 2 + 0.001, //move x
				(double)i + 0.2, //move y
				(double)j + 0.45 - 1,  //move z
				90);
		}
	}
	return b;
}

Building* BuildingsFactory::createSkyscraper(TextureFactory texFactory) {
	Building* b = new Building();
	Primitive* prim = new Cuboid(0, 0);
	Texture wallTexture = texFactory.getRandomWallTextureWithSpecifiedType(BuildingType::wiezowiec);
	setRandomHeight(prim, 1.4);
	prim->assignTexture(wallTexture);
	b->addMainPrimitive(prim);
	static RandomFactory rand;
	if (rand.getLinearValue(0, 100) < 5) {
		Primitive* roof = new Pyramid(0, 2 * b->getHeight(), 0); // times 2 because 2 lines later there is 0.5 scale
		roof->assignTexture(texFactory.getRandomTextureByType(dach));
		roof->scale(0.5);
		b->addPrimitive(roof);
	}
	setRandomWidth(b);
	return b;
}

Building* BuildingsFactory::createTenement(TextureFactory texFactory) {
	Building* b = new Building();
	Primitive* prim = new Cuboid(0, 0);
	Texture wallTexture = texFactory.getRandomWallTextureWithSpecifiedType(BuildingType::kamienica);
	setRandomHeight(prim, 0.8);
	prim->assignTexture(wallTexture);
	b->addMainPrimitive(prim);
	static RandomFactory rand;
	Primitive* roof = new TriangularPrism(0, 0, 0);
	roof->scale(1, (double)rand.getLinearValue(5,12) / 10, 1);
	roof->move(0, b->getHeight(), 0);
	((TriangularPrism*)roof)->assignTexture(wallTexture, texFactory.getRandomTextureByType(dach));
	b->addPrimitive(roof);
	setRandomWidth(b);
	return b;
}

Building* BuildingsFactory::createBlock(TextureFactory texFactory) {
	Building* b = new Building();
	Primitive* prim = new Cuboid(0, 0);
	Texture wallTexture = texFactory.getRandomWallTextureWithSpecifiedType(BuildingType::blok);
	setRandomHeight(prim, 1);
	prim->assignTexture(wallTexture);	
	b->addMainPrimitive(prim);
	setRandomWidth(b);
	return b;
}

Building* BuildingsFactory::setRandomHeight(Building* building) {
	static RandomFactory rand;
	building->setNewHeight(rand.getLogNormalValue());
	return building;
}

Primitive* BuildingsFactory::setRandomHeight(Primitive* prim, double ratio) {
	static RandomFactory rand;
	prim->setNewScaleHeight(rand.getLogNormalValue() * ratio);
	return prim;
}

Building* BuildingsFactory::setRandomWidth(Building* building) {
	static RandomFactory rand;
	building->scale(rand.getLogNormalValue(), 1, 1);
	return building;
}