#include "BinaryDivisionAlgorythmGenerator.h"

BinaryDivisionAlgorythmGenerator::BinaryDivisionAlgorythmGenerator(TextureFactory texFactory, unsigned divisionsNumber) {
	this->texFactory = texFactory;
	this->divisionsNumber = divisionsNumber;
}

BinaryDivisionAlgorythmGenerator::BinaryDivisionAlgorythmGenerator(TextureFactory texFactory, unsigned divisionsNumber, double xMin, double xMax, double zMin, double zMax) 
	: BinaryDivisionAlgorythmGenerator(texFactory, divisionsNumber){
	this->xMin = xMin;
	this->xMax = xMax;
	this->zMin = zMin;
	this->zMax = zMax;
}
Boundaries fun(Boundaries& bound) {
	return bound;
}

Point fun(Point& bound) {
	return bound;
}
std::vector<Street*> BinaryDivisionAlgorythmGenerator::generate() {
	//std::vector<Street*> streets;
	
	roadConnections.push_back(std::make_pair(Point(xMin, zMin), Point(xMin, zMax)));
	roadConnections.push_back(std::make_pair(Point(xMin, zMax), Point(xMax, zMax)));
	roadConnections.push_back(std::make_pair(Point(xMax, zMin), Point(xMax, zMax)));
	roadConnections.push_back(std::make_pair(Point(xMin, zMin), Point(xMax, zMin)));
	unsigned leftId = 0;
	unsigned topId = 1;
	unsigned rightId = 2;
	unsigned downId = 3;
	Boundaries bound(leftId, topId, rightId, downId);
	generateRecursive(0, bound, true);
	findPointsWithRoadConnections();
	if (!ignoreVisualObjects) {
		addStreets();
		addCrossings();
	}
	return streets;
}


Boundaries BinaryDivisionAlgorythmGenerator::generateRecursive(unsigned iter, Boundaries& bound, bool horizontal) {
	if (iter >= divisionsNumber)
		return bound;

	double minValX = roadConnections[bound.leftId[0]].first.x;
	double maxValX = roadConnections[bound.rightId[0]].first.x;
	double minValZ = roadConnections[bound.downId[0]].first.z;
	double maxValZ = roadConnections[bound.topId[0]].first.z;
	
	if (horizontal) {
		double mi = (minValX + maxValX) / 2;
		double sigma = (maxValX - minValX) / 6;
		double division = randomFactory.getNormalValue(mi, sigma);
		if (division < minValX || division > maxValX)
			division = mi;
	
		roadConnections.push_back(std::make_pair(Point(division, minValZ), Point(division, maxValZ)));
		unsigned foundTopId = findTopId(bound, division);
		unsigned foundDownId = findDownId(bound, division);
		unsigned newId1 = roadConnections.size() - 1;
		unsigned newId2 = divideRoadConnetion(foundTopId, division, horizontal);
		unsigned newId3 = divideRoadConnetion(foundDownId, division, horizontal);
		bound.topId.push_back(newId2);
		bound.downId.push_back(newId3);
		Boundaries boundLeft, boundRight;
		bound.splitHorizontal(foundTopId, foundDownId, newId1, roadConnections, boundLeft, boundRight);

		Boundaries boundRes1 = generateRecursive(iter + 1, boundLeft, !horizontal);
		boundRight.leftId.clear();
		boundRight.addAllLeft(boundRes1.rightId);

		Boundaries boundRes2 = generateRecursive(iter + 2, boundRight, !horizontal);
		Boundaries boundRes = boundRes1;
		boundRes.addAllTop(boundRes2.topId);
		boundRes.addAllDown(boundRes2.downId);
		boundRes.rightId.clear();
		boundRes.addAllRight(boundRes2.rightId);
		return boundRes;
	}
	else {
		double mi = (minValZ + maxValZ) / 2;
		double sigma = (maxValZ - minValZ) / 6;
		double division = randomFactory.getNormalValue(mi, sigma);
		if (division < minValZ || division > maxValZ)
			division = mi;

		roadConnections.push_back(std::make_pair(Point(minValX, division), Point(maxValX, division)));
		unsigned foundLeftId = findLeftId(bound, division);
		unsigned foundRightId = findRightId(bound, division);
		unsigned newId1 = roadConnections.size() - 1;
		unsigned newId2 = divideRoadConnetion(foundLeftId, division, horizontal);
		unsigned newId3 = divideRoadConnetion(foundRightId, division, horizontal);
		bound.leftId.push_back(newId2);
		bound.rightId.push_back(newId3);
		Boundaries boundDown, boundTop;
		bound.splitVertical(foundLeftId, foundRightId, newId1, roadConnections, boundDown, boundTop);

		Boundaries boundRes1 = generateRecursive(iter + 1, boundDown, !horizontal);
		boundTop.downId.clear();
		boundTop.addAllDown(boundRes1.topId);

		Boundaries boundRes2 = generateRecursive(iter + 2, boundTop, !horizontal);
		Boundaries boundRes = boundRes1;
		boundRes.addAllLeft(boundRes2.leftId);
		boundRes.addAllRight(boundRes2.rightId);
		boundRes.topId.clear();
		boundRes.addAllTop(boundRes2.topId);
		return boundRes;
	}
}

unsigned BinaryDivisionAlgorythmGenerator::divideRoadConnetion(unsigned connectionId, double division, bool horizontal) {
	Point temp = roadConnections[connectionId].second;
	if (horizontal) {
		roadConnections[connectionId].second = Point(division, temp.z);
		roadConnections.push_back(std::make_pair(Point(division, temp.z), temp));
	} 
	else {
		roadConnections[connectionId].second = Point(temp.x, division);
		roadConnections.push_back(std::make_pair(Point(temp.x, division), temp));
	}
	// returning new connetion ID
	return roadConnections.size() - 1;
}

void BinaryDivisionAlgorythmGenerator::findPointsWithRoadConnections() {
	std::set<Point> setOfPoints;
	for (auto con : roadConnections) {
		setOfPoints.insert(con.first);
		setOfPoints.insert(con.second);
	}
	for (auto p : setOfPoints) {
		roadsPoints.push_back(p);
	}
}

unsigned BinaryDivisionAlgorythmGenerator::findLeftId(Boundaries bound, double division) {
	return findConnectionId(bound.leftId, division, [](Point a) {return a.z; });
}
unsigned BinaryDivisionAlgorythmGenerator::findTopId(Boundaries bound, double division) {
	return findConnectionId(bound.topId, division, [](Point a) {return a.x; });
}
unsigned BinaryDivisionAlgorythmGenerator::findRightId(Boundaries bound, double division) {
	return findConnectionId(bound.rightId, division, [](Point a) {return a.z; });
}
unsigned BinaryDivisionAlgorythmGenerator::findDownId(Boundaries bound, double division) {
	return findConnectionId(bound.downId, division, [](Point a) {return a.x; });
}
unsigned BinaryDivisionAlgorythmGenerator::findConnectionId(std::vector<unsigned> ids, double division, double (*getParam)(Point)) {
	for (auto i : ids) 
		if (division >= (*getParam)(roadConnections[i].first) && division <= (*getParam)(roadConnections[i].second))
			return i;
}