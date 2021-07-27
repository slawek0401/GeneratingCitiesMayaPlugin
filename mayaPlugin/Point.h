#pragma once
class Point
{
public:
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	Point();
	Point(double x, double y, double z);
	Point(double x, double z);
	bool operator==(const Point& other) const;
	Point operator+=(const  Point& other);
	Point operator-=(const  Point& other);
	Point operator/=(double a);
	bool operator<(const Point &other) const;
	bool operator<=(const Point &other) const;
	bool operator>(const Point &other) const;
	bool operator>=(const Point &other) const;
};

