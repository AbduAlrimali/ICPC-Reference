/**
 * Author: common knowledge
 * Date: 2026-05-29
 * License: CC0
 * Description: Circle struct for geometry.
 * Status: untested
 */
#pragma once

#include "Point.h"
#include "Line.h"
#include "Segment.h"
#include "Polygon.h"

struct Circle {
	typedef Point<double> P;
	P p; double r;
	Circle(P p, double r) : p(p), r(r) {}

	vector<P> inter(Line<double> l) const {
		P ab = l.v();
		P pr = l.a + ab * (p - l.a).dot(ab) / ab.dist2();
		double s = l.a.cross(l.b, p), h2 = r * r - s * s / ab.dist2();
		if (h2 < 0) return {};
		if (h2 == 0) return {pr};
		P h = ab.unit() * sqrt(h2);
		return {pr - h, pr + h};
	}

	vector<P> inter(Segment<double> s) const {
		vector<P> res, tmp = inter(Line<double>(s.s, s.e));
		for (P x : tmp) if (s.on(x)) res.push_back(x);
		return res;
	}

	vector<P> inter(Circle c) const {
		P vec = c.p - p;
		double d2 = vec.dist2(), sum = r + c.r, dif = r - c.r;
		if (d2 > sum * sum || d2 < dif * dif || d2 == 0) return {};
		double a = (d2 + r * r - c.r * c.r) / (2 * d2);
		double h2 = r * r - a * a * d2;
		P mid = p + vec * a, per = vec.perp() * sqrt(fmax(0.0, h2) / d2);
		if (h2 <= 0) return {mid};
		return {mid + per, mid - per};
	}

	double interArea(Circle c) const {
		double d2 = (p - c.p).dist2(), d = sqrt(d2);
		if (r + c.r <= d) return 0;
		if (d <= abs(r - c.r)) return M_PI * pow(min(r, c.r), 2);
		auto sectorArea = [](double r, double otherR, double d) {
			double phi = 2 * acos((r * r + d * d - otherR * otherR) / (2 * r * d));
			return 0.5 * r * r * (phi - sin(phi));
		};
		return sectorArea(r, c.r, d) + sectorArea(c.r, r, d);
	}

	double interArea(const Polygon<double>& poly) const {
		auto tri = [&](P q, P w) {
			auto r2 = r * r / 2;
			P d = w - q;
			auto a = d.dot(q) / d.dist2(), b = (q.dist2() - r * r) / d.dist2();
			auto det = a * a - b;
			if (det <= 0) return atan2(q.cross(w), q.dot(w)) * r2;
			auto s = max(0., -a - sqrt(det)), t = min(1., -a + sqrt(det));
			if (t < 0 || 1 <= s) return atan2(q.cross(w), q.dot(w)) * r2;
			P u = q + d * s, v = w + d * (t - 1);
			return atan2(q.cross(u), q.dot(u)) * r2 + u.cross(v) / 2 + atan2(v.cross(w), v.dot(w)) * r2;
		};
		double sum = 0;
		int n = poly.size();
		for (int i = 0; i < n; i++)
			sum += tri(poly.p[i] - p, poly.p[(i + 1) % n] - p);
		return sum;
	}

	vector<pair<P, P>> tangents(Circle c) const {
		P d = c.p - p;
		double dr = r - c.r, d2 = d.dist2(), h2 = d2 - dr * dr;
		if (d2 == 0 || h2 < 0) return {};
		vector<pair<P, P>> out;
		for (double sign : {-1, 1}) {
			P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
			out.push_back({p + v * r, c.p + v * c.r});
		}
		if (h2 == 0) out.pop_back();
		return out;
	}

	static Circle circumcircle(P a, P b, P c) {
		P bb = c - a, cc = b - a;
		P ctr = a + (bb * cc.dist2() - cc * bb.dist2()).perp() / bb.cross(cc) / 2;
		return Circle(ctr, (ctr - a).dist());
	}

	static Circle incenter(P a, P b, P c) {
		double la = (b - c).dist(), lb = (a - c).dist(), lc = (a - b).dist();
		P res = (a * la + b * lb + c * lc) / (la + lb + lc);
		double area = abs((b - a).cross(c - a)) / 2;
		return Circle(res, 2 * area / (la + lb + lc));
	}

	static Circle minEnclosing(vector<P> ps) {
		shuffle(ps.begin(), ps.end(), mt19937(time(0)));
		P o = ps[0];
		double r = 0, EPS = 1 + 1e-8;
		for (int i = 0; i < (int)ps.size(); i++) if ((o - ps[i]).dist() > r * EPS) {
			o = ps[i], r = 0;
			for (int j = 0; j < i; j++) if ((o - ps[j]).dist() > r * EPS) {
				o = (ps[i] + ps[j]) / 2, r = (o - ps[i]).dist();
				for (int k = 0; k < j; k++) if ((o - ps[k]).dist() > r * EPS) {
					Circle c = circumcircle(ps[i], ps[j], ps[k]);
					o = c.p, r = c.r;
				}
			}
		}
		return Circle(o, r);
	}
};
