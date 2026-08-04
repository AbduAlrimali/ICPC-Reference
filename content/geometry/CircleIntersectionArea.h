/**
 * Author: common
 * Date: 2024-05-27
 * License: CC0
 * Description: Area of intersection of two circles.
 * Status: tested
 */
#pragma once
#include "Point.h"

double circleIntersectionArea(Point<double> c1, double r1, Point<double> c2, double r2) {
	double d2 = (c1 - c2).dist2(), d = sqrt(d2);
	if (r1 + r2 <= d) return 0;
	if (d <= abs(r1 - r2)) {
		double r = min(r1, r2);
		return PI * r * r;
	}
	auto sectorArea = [](double r, double otherR, double d) {
		double phi = 2 * acos((r * r + d * d - otherR * otherR) / (2 * r * d));
		return 0.5 * r * r * (phi - sin(phi));
	};
	return sectorArea(r1, r2, d) + sectorArea(r2, r1, d);
}
