/**
 * Author: common
 * Date: 2024-05-27
 * License: CC0
 * Description: Minkowski sum of two convex polygons. Both must be CCW.
 * Returns a CCW polygon.
 * Time: O(n+m)
 * Status: tested
 */
#pragma once
#include "Point.h"

template<class P>
vector<P> minkowskiSum(vector<P> a, vector<P> b) {
	auto reorder = [&](vector<P>& p) {
		int pos = 0;
		rep(i,1,sz(p)) if (p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x)) pos = i;
		rotate(p.begin(), p.begin() + pos, p.end());
	};
	if (a.empty() || b.empty()) return {};
	reorder(a); reorder(b);
	int n = sz(a), m = sz(b), i = 0, j = 0;
	vector<P> res;
	while (i < n || j < m) {
		res.push_back(a[i % n] + b[j % m]);
		auto c = (a[(i + 1) % n] - a[i % n]).cross(b[(j + 1) % m] - b[j % m]);
		if (c >= 0 && i < n) i++;
		if (c <= 0 && j < m) j++;
	}
	return res;
}
