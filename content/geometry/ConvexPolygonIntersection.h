/**
 * Author: common
 * Date: 2024-05-27
 * License: CC0
 * Description: Returns the vertices of the intersection of two convex polygons.
 * Both must be CCW.
 * Time: O(N \cdot M)
 * Status: tested
 */
#pragma once
#include "PolygonCut.h"

typedef Point<double> P;
vector<P> convexPolygonIntersection(vector<P> a, vector<P> b) {
	vector<P> res = a;
	rep(i,0,sz(b)) {
		res = polygonCut(res, b[i], b[(i + 1) % sz(b)]);
	}
	return res;
}
