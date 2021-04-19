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

bool Point::operator==(Point& other) {
	return this->x == other.x && this->y == other.y && this->z == other.z;
}

Point Point::operator+=(const Point& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Point Point::operator-=(const Point& other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Point Point::operator/=(double a) {
	this->x /= a;
	this->y /= a;
	this->z /= a;
	return *this;
}