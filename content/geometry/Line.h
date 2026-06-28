/**
 * Author: common knowledge
 * Date: 2026-05-29
 * License: CC0
 * Description: Line struct for geometry.
 * Status: untested
 */
#pragma once

#include "Point.h"

template<class T>
struct Line {
	typedef Point<T> P;
	P a, b;
	Line(P a, P b) : a(a), b(b) {}
	P v() const { return b - a; }
	// Signed distance from line ab to point p. 
	// Positive on left side, negative on right.
	double dist(P p) const { return (double)v().cross(p - a) / v().dist(); }
	T dist2(P p) const { T c = v().cross(p - a); return c * c / v().dist2(); }
	int sideOf(P p) const { return sgn(v().cross(p - a)); }
	P proj(P p) const { return a + v() * v().dot(p - a) / v().dist2(); }
	P refl(P p) const { return proj(p) * 2 - p; }
	pair<int, P> inter(Line l) const {
		auto d = v().cross(l.v());
		if (d == 0) return {-(a.cross(b, l.a) == 0), P(0, 0)};
		return {1, (a * l.a.cross(b, l.b) + b * l.a.cross(l.b, a)) / d};
	}
};
