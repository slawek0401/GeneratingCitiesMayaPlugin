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

Building* BuildingsFactory::createHouse(TextureFactory texFactory) {
	static RandomFactory rand;
	Building* b = new Building();
	Primitive* prim = new Cuboid(0, 0);
	Texture wallTexture = texFactory.getRandomWallTextureWithSpecifiedType(BuildingType::dom_jednorodzinny);
	prim->assignTexture(wallTexture);
	prim->setNewHeight(rand.getLinearValue(1,2));
	b->addMainPrimitive(prim);
	Primitive* roof;
	if (rand.getLinearValue(0, 1) == 0) {
		roof = new Pyramid(0, b->getHeight(), 0);
		roof->assignTexture(texFactory.getRandomTextureByType(dach));
	}
	else {
		roof = new TriangularPrism(0, b->getHeight(), 0);
		((TriangularPrism*)roof)->assignTexture(wallTexture, texFactory.getRandomTextureByType(dach));
	}
	b->addPrimitive(roof);
	setRandomWidth(b);
	return b;
}

Building* BuildingsFactory::createSkyscraper(TextureFactory texFactory) {
	Building* b = new Building();
	Primitive* prim = new Cuboid(0, 0);
	Texture wallTexture = texFactory.getRandomWallTextureWithSpecifiedType(BuildingType::wiezowiec);
	prim->assignTexture(wallTexture);
	setRandomHeight(prim, 1.4);
	b->addMainPrimitive(prim);
	static RandomFactory rand;
	if (rand.getLinearValue(0, 100) < 5) {
		Primitive* roof = new Pyramid(0, b->getHeight(), 0);
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
	prim->assignTexture(wallTexture);
	setRandomHeight(prim, 0.8);
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
	prim->assignTexture(wallTexture);
	setRandomHeight(prim, 1);
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