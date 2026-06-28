/**
 * Author: User
 * Date: 2026-06-05
 * License: CC0
 * Source: user
 * Description: Persistent/Dynamic Li Chao Tree for line minimum queries.
 * Each update creates a new version (root).
 * Time: $O(\log N)$ per update and query.
 * Status: unknown
 */
#pragma once

struct Line {
	ll k, d;
	ll eval(ll x) { return k * x + d; }
};

struct LiChaoNode {
	Line line;
	int l, r;
	LiChaoNode() : line({0, (ll)2e18}), l(0), r(0) {}
	LiChaoNode(Line line) : line(line), l(0), r(0) {}
};

const int MAX_NODES = 5000005;
LiChaoNode t[MAX_NODES];
int T_cnt = 1;

int upd(int pre, Line nw, int l, int r) {
	int id = ++T_cnt;
	t[id] = t[pre];
	int m = l + (r - l) / 2;
	bool lef = nw.eval(l) < t[id].line.eval(l);
	bool mid = nw.eval(m) < t[id].line.eval(m);
	if (mid) swap(t[id].line, nw);
	if (l == r) return id;
	if (lef != mid) {
		if (!t[pre].l) {
			t[id].l = ++T_cnt;
			t[T_cnt] = LiChaoNode(nw);
		} else {
			t[id].l = upd(t[pre].l, nw, l, m);
		}
	} else {
		if (!t[pre].r) {
			t[id].r = ++T_cnt;
			t[T_cnt] = LiChaoNode(nw);
		} else {
			t[id].r = upd(t[pre].r, nw, m + 1, r);
		}
	}
	return id;
}

ll Query(int cur, int x, int l, int r) {
	if (!cur) return 2e18;
	ll val = t[cur].line.eval(x);
	if (l == r) return val;
	int m = l + (r - l) / 2;
	if (x <= m) val = min(val, Query(t[cur].l, x, l, m));
	else val = min(val, Query(t[cur].r, x, m + 1, r));
	return val;
}

struct PersistentLiChaoTree {
	int L, R;
	vector<int> roots;
	PersistentLiChaoTree(int L = -1e9, int R = 1e9) : L(L), R(R) {
		roots = {1};
	}
	void add_line(int version, Line line) {
		roots.push_back(upd(roots[version], line, L, R));
	}
	ll query(int version, int x) {
		return Query(roots[version], x, L, R);
	}
};

// PersistentLiChaoTree lt(-1e9, 1e9);
// lt.add_line({m1, c1}); // version 1
// lt.add_line({m2, c2}); // version 2
// ll res = lt.query(1, x); // Query version 1 at position x

