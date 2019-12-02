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

	float u[4] = {
			0.0, 1.0, 1.0, 0.0
	};
	float v[4] = {
			0.0, 0.0, length*2, length*2
	};
	int ids[4] = {
			0,3,2,1
	};
	UVcounts.append(4);
	for (int i = 0; i < 4; ++i)
		UVids.append(ids[i]);
	for (int i = 0; i < 4; ++i)
		uArray.append(u[i]);
	for (int i = 0; i < 4; ++i)
		vArray.append(v[i]);
}


Street::~Street()
{
}
