#include "Street.h"



Street::Street(int x1, int z1, int width, int length)
{
	vert.append(MFloatPoint(x1, 0, z1));
	vert.append(MFloatPoint(x1, 0, z1 + length));
	vert.append(MFloatPoint(x1 + width, 0, z1 + length));
	vert.append(MFloatPoint(x1 + width, 0, z1));

	polCounts.append(4);

	polConnects.append(0);
	polConnects.append(1);
	polConnects.append(2);
	polConnects.append(3);
}


Street::~Street()
{
}
