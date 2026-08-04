/**
 * Author: chilli
 * Date: 2026-07-16
 * Description: Finds the intersection between a circle and a segment.
 * Returns a vector of either 0, 1, or 2 intersection points.
 * Status: tested
 */
#pragma once

#include "CircleLine.h"

template<class P>
vector<P> circleSegment(P c, double r, P a, P b) {
	vector<P> pts = circleLine(c, r, a, b);
	vector<P> res;
	for (P p : pts) {
		if ((a - p).dot(b - p) <= 1e-9) {
			res.push_back(p);
		}
	}
	return res;
}
