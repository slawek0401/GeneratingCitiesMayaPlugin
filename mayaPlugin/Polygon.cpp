#include "Polygon.h"

Polygon::Polygon(std::vector<Point> points) {

	for (auto p : points)
		vert.append(MFloatPoint(p.x, p.y, p.z));
	
	polCounts.append(points.size());

	for (unsigned i = 0; i < points.size(); ++i)
		polConnects.append(i);

	oneTextureOnWhole = true;
	Point zMin = *std::min_element(points.begin(), points.end(), [](Point a, Point b) {return a.z < b.z; });
	Point zMax = *std::max_element(points.begin(), points.end(), [](Point a, Point b) {return a.z < b.z; });
	Point xMin = *std::min_element(points.begin(), points.end(), [](Point a, Point b) {return a.x < b.x; });
	Point xMax = *std::max_element(points.begin(), points.end(), [](Point a, Point b) {return a.x < b.x; });
	Point minPoint(xMin.x, 0, zMin.z);
	Point diagPoint(xMax.x - xMin.x, 0, zMax.z - zMin.z);

	for (unsigned long i = 0; i < points.size(); ++i)
		points[i] += minPoint;

	for (unsigned long i = 0; i < points.size(); ++i)
		points[i] /= std::max(diagPoint.x, diagPoint.z);
	

	UVcounts.append(points.size());
	for (int i = 0; i < points.size(); ++i)
		UVids.append(i);
	for (auto p : points) {
		uArray.append(p.x);
		vArray.append(p.z);
	}	
}

Polygon::~Polygon() {};