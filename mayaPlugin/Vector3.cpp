#include "Vector3.h"

Vector3::Vector3(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(Point a, Point b) {
	this->x = b.x - a.x;
	this->y = b.y - a.y;
	this->z = b.z - a.z;
}

Vector3::Vector3(const Vector3& other) {
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

void Vector3::rotateY(double degrees) {
	double degInRad = degrees * M_PI / 180;
	auto oldX = x;
	auto oldZ = z;
	x = cos(degInRad) * oldX - sin(degInRad) * oldZ;
	z = sin(degInRad) * oldX + cos(degInRad) * oldZ;
}

double Vector3::countLength() {
	return sqrt(x*x + y*y + z*z);
}

void Vector3::normalize() {
	double length = countLength();
	x = x / length;
	y = y / length;
	z = z / length;
}

std::pair<Point, Point> Vector3::toPoints(Point start) {
	return toPoints(start.x, start.y, start.z);
}

std::pair<Point, Point> Vector3::toPoints(double x_, double y_, double z_) {
	Point a(x_, y_, z_);
	Point b(x_ + x, y_ + y, z_ + z);
	return std::make_pair(a, b);
}

void Vector3::scale(double a){
	x = a * x;
	y = a * y;
	z = a * z;
}

void Vector3::setLength(double length) {
	normalize();
	scale(length);
}

Vector3 Vector3::operator+(const Vector3& other) {
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

double Vector3::angle() {
	auto val = atan(z / x);
	if (x < 0)
		val += (z < 0 ? -1 : 1) * M_PI;
	return val;
}

double Vector3::countSectionLength(Point a, Point b) {
	double x = b.x - a.x;
	double y = b.y - a.y;
	double z = b.z - a.z;
	return sqrt(x * x + y * y + z * z);
}

double Vector3::countSectionLength(std::pair<Point, Point> a) {
	return Vector3::countSectionLength(a.first, a.second);
}

double Vector3::countSectionLength(RoadConnection a) {
	return Vector3::countSectionLength(a.first, a.second);
}