/**
 * Author: user
 * Date: 2026-07-08
 * License: CC0
 * Source: rotating calipers modification
 * Description: Returns all unique antipodal pairs of a convex hull
 * (ccw, no duplicate/collinear points).
 * Time: O(n \log n) due to sorting, or O(n) if sorted output not needed.
 * Status: tested
 */
#pragma once
#include "Point.h"

typedef Point<ll> P;
vector<pair<int, int>> antipodalPairs(vector<P> &S) {
	int n = sz(S);
	if (n < 2) return {};
	if (n == 2) return {{0, 1}};
	vector<pair<int, int>> pairs;
	auto add = [&](int u, int v) {
		if (u > v) swap(u, v);
		pairs.push_back({u, v});
	};
	int j = 1;
	rep(i,0,n) {
		while (true) {
			ll diff = (S[(i + 1) % n] - S[i])
				.cross(S[(j + 1) % n] - S[j]);
			if (diff > 0) j = (j + 1) % n;
			else break;
		}
		add(i, j);
		add((i + 1) % n, j);
		ll diff = (S[(i + 1) % n] - S[i])
			.cross(S[(j + 1) % n] - S[j]);
		if (diff == 0) {
			add(i, (j + 1) % n);
			add((i + 1) % n, (j + 1) % n);
		}
	}
	sort(all(pairs));
	pairs.erase(unique(all(pairs)), pairs.end());
	return pairs;
}
