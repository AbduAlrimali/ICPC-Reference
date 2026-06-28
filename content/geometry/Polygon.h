/**
 * Author: common knowledge
 * Date: 2026-05-29
 * License: CC0
 * Description: Polygon struct for geometry.
 * Status: untested
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

template<class T>
struct Polygon {
	typedef Point<T> P;
	vector<P> p;
	Polygon(vector<P> p) : p(p) {}
	int size() const { return (int)p.size(); }
	T area2() const {
		T a = p.back().cross(p[0]);
		for (int i = 0; i < (int)p.size() - 1; i++) a += p[i].cross(p[i+1]);
		return a;
	}
	double area() const { return abs((double)area2() / 2.0); }
	bool isConvex() const {
		int n = (int)p.size(), pos = 0, neg = 0;
		for (int i = 0; i < n; i++) {
			T c = p[i].cross(p[(i+1)%n], p[(i+2)%n]);
			if (c > 0) pos++;
			if (c < 0) neg++;
		}
		return pos == 0 || neg == 0;
	}
	bool inside(P a, bool strict = true) const {
		int cnt = 0, n = (int)p.size();
		for (int i = 0; i < n; i++) {
			P q = p[(i + 1) % n];
			if (onSegment(p[i], q, a)) return !strict;
			cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
		}
		return cnt;
	}
	Point<double> center() const {
		Point<double> res(0, 0); double A = 0;
		for (int i = 0, j = (int)p.size() - 1; i < (int)p.size(); j = i++) {
			double c = (double)p[j].cross(p[i]);
			res = res + (Point<double>(p[i].x, p[i].y) + Point<double>(p[j].x, p[j].y)) * c;
			A += c;
		}
		return res / A / 3;
	}
	Polygon cut(P s, P e) const {
		vector<P> res;
		for (int i = 0; i < (int)p.size(); i++) {
			P cur = p[i], prev = i ? p[i-1] : p.back();
			auto a = s.cross(e, cur), b = s.cross(e, prev);
			if ((a < 0) != (b < 0))
				res.push_back(cur + (prev - cur) * ((double)a / (a - b)));
			if (a < 0) res.push_back(cur);
		}
		return Polygon(res);
	}
	static Polygon convexHull(vector<P> pts) {
		if (pts.size() <= 1) return Polygon(pts);
		sort(pts.begin(), pts.end());
		vector<P> h(pts.size() + 1);
		int s = 0, t = 0;
		for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
			for (P x : pts) {
				while (t >= s + 2 && h[t-2].cross(h[t-1], x) <= 0) t--;
				h[t++] = x;
			}
		return Polygon({h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])});
	}
	array<P, 2> diameter() const {
		int n = (int)p.size(), j = n < 2 ? 0 : 1;
		pair<T, array<P, 2>> res({0, {p[0], p[0]}});
		for (int i = 0; i < j; i++)
			for (;; j = (j + 1) % n) {
				res = max(res, {(p[i] - p[j]).dist2(), {p[i], p[j]}});
				if ((p[(j + 1) % n] - p[j]).cross(p[i + 1] - p[i]) >= 0) break;
			}
		return res.second;
	}
	bool inHull(P a, bool strict = true) const {
		int n = (int)p.size(), i = 1, j = n - 1, r = !strict;
		if (n < 3) return r && onSegment(p[0], p.back(), a);
		if (p[0].cross(p[i], p[j]) > 0) swap(i, j);
		if (p[0].cross(p[i], a) >= r || p[0].cross(p[j], a) <= -r) return false;
		while (abs(i - j) > 1) {
			int c = (i + j) / 2;
			(p[0].cross(p[c], a) > 0 ? j : i) = c;
		}
		return sgn(p[i].cross(p[j], a)) < r;
	}
};
