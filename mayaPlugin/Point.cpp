#include "Point.h"

Point::Point() {

}

Point::Point(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::Point(double x, double z) {
	this->x = x;
	this->z = z;
}