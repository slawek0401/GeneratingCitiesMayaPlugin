#include "Street.h"



Street::Street(int x1=1, int z1=1, int width=2, int length=2)
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
