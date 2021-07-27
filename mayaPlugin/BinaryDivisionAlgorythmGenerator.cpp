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

	generateRecursive(0, leftId, topId, rightId, downId, true);
	findPointsWithRoadConnections();
	addStreets();
	addCrossings();
	showDebug("binary");
	showDebug(std::to_string(divisionsNumber));
	showDebug(std::to_string(roadConnections.size()));
	showDebug(std::to_string(streets.size()));
	showDebug(std::to_string(roadsPoints.size()));
	return streets;
}

void BinaryDivisionAlgorythmGenerator::generateRecursive(unsigned iter, unsigned leftId, unsigned topId, unsigned rightId, unsigned downId, bool horizontal) {
	if (iter >= divisionsNumber)
		return;
	showDebug("dupa");
	double minValX = roadConnections[leftId].first.x;
	double maxValX = roadConnections[rightId].first.x;
	double minValZ = roadConnections[downId].first.z;
	double maxValZ = roadConnections[topId].first.z;
	
	if (horizontal) {
		double mi = (minValX + maxValX) / 2;
		double sigma = (maxValX - minValX) / 6;
		double division = randomFactory.getNormalValue(mi, sigma);
		if (division < minValX || division > maxValX)
			division = mi;
	
		roadConnections.push_back(std::make_pair(Point(division, minValZ), Point(division, maxValZ)));
		unsigned newId1 = roadConnections.size() - 1;
		unsigned newId2 = divideRoadConnetion(topId, division, horizontal);
		unsigned newId3 = divideRoadConnetion(downId, division, horizontal);
		generateRecursive(iter + 1, leftId, topId, newId1, downId, !horizontal);
		generateRecursive(iter + 2, newId1, newId2, rightId, newId3, !horizontal);
	}
	else {
		double mi = (minValZ + maxValZ) / 2;
		double sigma = (maxValZ - minValZ) / 6;
		double division = randomFactory.getNormalValue(mi, sigma);
		if (division < minValZ || division > maxValZ)
			division = mi;

		roadConnections.push_back(std::make_pair(Point(minValX, division), Point(maxValX, division)));
		unsigned newId1 = roadConnections.size() - 1;
		unsigned newId2 = divideRoadConnetion(leftId, division, horizontal);
		unsigned newId3 = divideRoadConnetion(rightId, division, horizontal);
		generateRecursive(iter + 1, leftId, topId, rightId, newId1, !horizontal);
		generateRecursive(iter + 2, newId1, newId1, newId3, downId , !horizontal);
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