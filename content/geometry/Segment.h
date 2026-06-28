/**
 * Author: common knowledge
 * Date: 2026-05-29
 * License: CC0
 * Description: Segment struct for geometry.
 * Status: untested
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

template<class T>
struct Segment {
	typedef Point<T> P;
	P s, e;
	Segment(P s, P e) : s(s), e(e) {}
	double dist(P p) const {
		if (s == e) return (p - s).dist();
		auto d = (e - s).dist2(), t = min(d, max((T)0, (p - s).dot(e - s)));
		return ((p - s) * d - (e - s) * t).dist() / d;
	}
	bool on(P p) const { return onSegment(s, e, p); }
	vector<P> inter(Segment o) const {
		auto oa = o.s.cross(o.e, s), ob = o.s.cross(o.e, e),
		     oc = s.cross(e, o.s), od = s.cross(e, o.e);
		if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
			return {(s * ob - e * oa) / (ob - oa)};
		set<P> res;
		if (on(o.s)) res.insert(o.s);
		if (on(o.e)) res.insert(o.e);
		if (o.on(s)) res.insert(s);
		if (o.on(e)) res.insert(e);
		return {res.begin(), res.end()};
	}
	double dist(Segment o) const {
		if (!inter(o).empty()) return 0;
		return min({dist(o.s), dist(o.e), o.dist(s), o.dist(e)});
	}
};
