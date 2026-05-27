/**
 * Author: common
 * Date: 2024-05-27
 * License: CC0
 * Description: Half-plane intersection. Each line (s, e) represents the half-plane to the left of s->e.
 * Returns vertices of the intersection polygon in CCW order.
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once
#include "Point.h"
#include "lineIntersection.h"

struct Halfplane {
	Point<double> s, e; double ang;
	Halfplane() {}
	Halfplane(Point<double> _s, Point<double> _e) : s(_s), e(_e) {
		ang = atan2((e - s).y, (e - s).x);
	}
	bool out(Point<double> p) { return (e - s).cross(p - s) < -1e-9; }
	bool operator<(const Halfplane& b) const {
		if (abs(ang - b.ang) > 1e-9) return ang < b.ang;
		return (e - s).cross(b.s - s) < -1e-9;
	}
};

vector<Point<double>> halfPlaneIntersection(vector<Halfplane> h) {
	sort(all(h));
	deque<Halfplane> dq;
	rep(i,0,sz(h)) {
		if (i && abs(h[i].ang - h[i-1].ang) < 1e-9) continue;
		while (sz(dq) >= 2 && h[i].out(lineInter(dq[sz(dq)-2].s, dq[sz(dq)-2].e, dq.back().s, dq.back().e).second))
			dq.pop_back();
		while (sz(dq) >= 2 && h[i].out(lineInter(dq[0].s, dq[0].e, dq[1].s, dq[1].e).second))
			dq.pop_front();
		dq.push_back(h[i]);
	}
	while (sz(dq) >= 3 && dq[0].out(lineInter(dq[sz(dq)-2].s, dq[sz(dq)-2].e, dq.back().s, dq.back().e).second))
		dq.pop_back();
	while (sz(dq) >= 3 && dq.back().out(lineInter(dq[0].s, dq[0].e, dq[1].s, dq[1].e).second))
		dq.pop_front();
	if (sz(dq) < 3) return {};
	vector<Point<double>> res;
	rep(i,0,sz(dq)) res.push_back(lineInter(dq[i].s, dq[i].e, dq[(i+1)%sz(dq)].s, dq[(i+1)%sz(dq)].e).second);
	return res;
}
