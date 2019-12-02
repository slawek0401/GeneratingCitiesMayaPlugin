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

void Street::addBuildingAlongAbsolute(MFloatPoint from, MFloatPoint to) {
	buildingsAlong.push_back(from);
	buildingsAlong.push_back(to);
}

void Street::addBuildingAlongRelative(float from, float to, bool left) {
	MFloatPoint rel = left ? vert[0] : vert[3];
	buildingsAlong.push_back(MFloatPoint(rel.x + from, rel.y, rel.z));
	buildingsAlong.push_back(MFloatPoint(rel.x + to, rel.y, rel.z));
}

void Street::addBuildingAlongAllStreet() {
	buildingsAlong.push_back(vert[0]);
	buildingsAlong.push_back(vert[1]);
	buildingsAlong.push_back(vert[3]);
	buildingsAlong.push_back(vert[2]);
}

std::vector<MFloatPoint> Street::getBuildingsAlong() {
	return buildingsAlong;
}