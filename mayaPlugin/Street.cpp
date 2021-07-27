#include "Street.h"



Street::Street(BuildingType bType, double walkPathFrac, double x1, double z1, double width, double length)
{
	this->neighbourhood = bType;
	this->width = width;
	this->length = length;
	this->walkPathFrac = walkPathFrac;

	/*
	0-4---7-3
	| |   | |
	| |   | |
	| |   | |
	1-5---6-2
	*/
	vert.append(MFloatPoint(x1, 0, z1)); //0
	vert.append(MFloatPoint(x1, 0, z1 + length)); //1
	vert.append(MFloatPoint(x1 + width, 0, z1 + length)); //2
	vert.append(MFloatPoint(x1 + width, 0, z1)); //3

	vert.append(MFloatPoint(x1 + walkPathFrac * width, 0, z1)); //4
	vert.append(MFloatPoint(x1 + walkPathFrac * width, 0, z1 + length)); //5
	vert.append(MFloatPoint(x1 + (1 - walkPathFrac) * width, 0, z1 + length)); //6
	vert.append(MFloatPoint(x1 + (1 - walkPathFrac) * width, 0, z1)); //7
	
	for (int i = 0; i < 3; ++i)
		polCounts.append(4);

	polConnects.append(0); //chodnik
	polConnects.append(1);
	polConnects.append(5);
	polConnects.append(4);

	polConnects.append(4); //jezdnia
	polConnects.append(5);
	polConnects.append(6);
	polConnects.append(7);

	polConnects.append(7); //chodnik
	polConnects.append(6);
	polConnects.append(2);
	polConnects.append(3);

	oneTextureOnWhole = false;
	std::vector<int> walkPaths{ 0, 2 };
	std::vector<int> road{ 1 };
	texOnFaceIndexes.push_back(walkPaths); 
	texOnFaceIndexes.push_back(road); 

	float u[4] = {
			0.0, 1.0, 1.0, 0.0
	};
	float v[4] = {
			0.0, 0.0, length*2, length*2
	};
	int ids[] = {
			0,3,2,1,
			0,3,2,1,
			0,3,2,1
	};
	for (int i = 0; i < 3; ++i)
		UVcounts.append(4);
	for (int i = 0; i < 12; ++i)
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

//void Street::addBuildingAlongRelative(float from, float to, bool left) {
//	MFloatPoint rel = left ? vert[0] : vert[2];
//	float wsp = left ? 1.0 : -1.0;
//	buildingsAlong.push_back(MFloatPoint(rel.x + from*wsp, rel.y, rel.z));
//	buildingsAlong.push_back(MFloatPoint(rel.x + to*wsp, rel.y, rel.z));
//}

void Street::addBuildingAlongRelative(float from, float to, bool left){//(const MFloatPoint& v1, const MFloatPoint& v2, Building* b, std::vector<Building*>& vec, const MFloatPoint& curr) {
	MFloatPoint v1 = left ? vert[0] : vert[2];
	MFloatPoint v2 = left ? vert[1] : vert[3];
	//double alfa1 = atan((v1.z - v2.z) / (v1.x - v2.x));
	//float wsp;
	//if (asin((v1.z - v2.z) / sqrt(pow(v1.z - v2.z, 2) + pow(v1.x - v2.x, 2))) == 0)
	//	wsp = acos((v1.x - v2.x) / sqrt(pow(v1.z - v2.z, 2) + pow(v1.x - v2.x, 2))) > 0 ? 1.0 : -1.0;
	//else
	//	wsp = -1;
	//buildingsAlong.push_back(MFloatPoint( wsp * from * cos(alfa1) + v1.x, 0, wsp * from * sin(alfa1) + v1.z));
	//buildingsAlong.push_back(MFloatPoint( wsp * to * cos(alfa1) + v1.x, 0, wsp * to * sin(alfa1) + v1.z));
	Vector3 v(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
	Vector3 u(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
	v.setLength(from);
	auto p1 = v.toPoints(v1.x, v1.y, v1.z).second;
	u.setLength(to);
	auto p2 = u.toPoints(v1.x, v1.y, v1.z).second;
	buildingsAlong.push_back(MFloatPoint(p1.x, p1.y, p1.z));
	buildingsAlong.push_back(MFloatPoint(p2.x, p2.y, p2.z));
	//std::string a1 = std::to_string(from) + "    " + std::to_string(to);
	//MString c1(a1.data());
	//MGlobal::displayInfo(c1);	
	//std::string a = std::to_string(p1.x) + "  " + std::to_string(p1.y) + "  " + std::to_string(p1.z) + "        " + std::to_string(p2.x) + "  " + std::to_string(p2.y) + "  " + std::to_string(p2.z);
	//MString c(a.data());
	//MGlobal::displayInfo(c);
}

void Street::addBuildingAlongAllStreet() {
	buildingsAlong.push_back(vert[0]);
	buildingsAlong.push_back(vert[1]);
	buildingsAlong.push_back(vert[2]);
	buildingsAlong.push_back(vert[3]);
}

std::vector<MFloatPoint> Street::getBuildingsAlong() {
	return buildingsAlong;
}

BuildingType Street::getNeighbourhood() {
	return neighbourhood;
}

void Street::setNeighbourhood(BuildingType bType) {
	this->neighbourhood = bType;
}

void Street::assignTexture(Texture walkPaths, Texture road) {
	textures.push_back(walkPaths);
	textures.push_back(road);
}

void Street::assignTexture(Texture road) {
	textures.push_back(road);
}

void Street::setParkOnLeft() {
	parkOnLeft = true;
}

bool Street::isParkOnLeft() {
	return parkOnLeft;
}

double Street::getWidth() {
	return width;
}

double Street::getLength() {
	return length;
}

double Street::getWalkPathFrac() {
	return walkPathFrac;
}