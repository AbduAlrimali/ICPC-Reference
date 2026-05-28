/**
 * Author: Unknown
 * Date: 2026-05-28
 * License: CC0
 * Source: folklore
 * Description: Pick's Theorem: $A = I + B/2 - 1$, where $A$ is the area,
 * $I$ is the number of interior lattice points, and $B$ is the number of boundary lattice points.
 * For boundary points $B = \sum \gcd(|x_{i+1}-x_i|, |y_{i+1}-y_i|)$.
 * Status: Tested
 */
#pragma once

#include "Point.h"

ll countBoundaryPoints(const vector<Point<ll>>& v) {
	ll b = 0;
	rep(i,0,sz(v)) {
		Point<ll> d = v[i] - v[(i + 1) % sz(v)];
		b += gcd(abs(d.x), abs(d.y));
	}
	return b;
}

// I = (2A - B + 2) / 2
ll countInteriorPoints(ll area2, ll b) {
	return (abs(area2) - b + 2) / 2;
}
