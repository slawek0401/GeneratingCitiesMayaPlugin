#include "Building.h"

Building::Building()
{
}


Building::~Building()
{
}

MFloatPointArray Building::getVert() {
	return vert;
}

MIntArray Building::getpolCounts() {
	return polCounts;
}

MIntArray Building::getpolConnects() {
	return polConnects;
}

void Building::setAsCuboid(int moveX, int moveZ)
{
	vert.append(MFloatPoint(1 + moveX, 5, 1 + moveZ));
	vert.append(MFloatPoint(-1 + moveX, 5, 1 + moveZ));
	vert.append(MFloatPoint(-1 + moveX, 0, 1 + moveZ));
	vert.append(MFloatPoint(1 + moveX, 0, 1 + moveZ));
	vert.append(MFloatPoint(1 + moveX, 5, -1 + moveZ));
	vert.append(MFloatPoint(-1 + moveX, 5, -1 + moveZ));
	vert.append(MFloatPoint(-1 + moveX, 0, -1 + moveZ));
	vert.append(MFloatPoint(1 + moveX, 0, -1 + moveZ));


	for (int i = 0; i < 6; ++i)
		polCounts.append(4);


	polConnects.append(0);
	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(3);

	polConnects.append(4);
	polConnects.append(5);
	polConnects.append(6);
	polConnects.append(7);

	polConnects.append(0);
	polConnects.append(1);
	polConnects.append(5);
	polConnects.append(4);

	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(6);
	polConnects.append(5);

	polConnects.append(2);
	polConnects.append(3);
	polConnects.append(7);
	polConnects.append(6);

	polConnects.append(0);
	polConnects.append(3);
	polConnects.append(7);
	polConnects.append(4);
}