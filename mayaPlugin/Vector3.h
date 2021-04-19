#pragma once

#include <corecrt_math_defines.h>
#include <cmath>
#include <vector>
#include "Point.h"

class Vector3
{
public:
	double x, y, z;

private:
	double countLength();

public:
	Vector3(double x, double y, double z);
	Vector3(Point a, Point b);
	Vector3(const Vector3& other);
	void rotateY(double degrees);
	void normalize();
	void scale(double a);
	void setLength(double length);
	double angle();
	std::pair<Point, Point> toPoints(Point start);
	std::pair<Point, Point> toPoints(double x, double y, double z);
	Vector3 operator+(const Vector3& other);
};

