#include "RoadConnection.h"

RoadConnection::RoadConnection(Point first, Point second) {
	this->first = first;
	this->second = second;
}

RoadConnection::RoadConnection(Point first, Point second, double width) : RoadConnection(first, second) {
	this->width = width;
}