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

bool Point::operator==(const Point& other) const {
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

bool Point::operator< (const Point &other) const {
	if (this->x == other.x)
		if (this->y == other.y)
			return this->z < other.z;
		else
			return this->y < other.y;
	return this->x < other.x;
}

bool Point::operator<= (const Point &other) const {
	return *this == other || *this < other;
}

bool Point::operator> (const Point &other) const {
	return !(*this <= other);
}

bool Point::operator>= (const Point &other) const {
	return !(*this < other);
}