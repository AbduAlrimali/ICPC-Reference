/**
 * Author: Abdua
 * Date: 2026-05-30
 * License: CC0
 * Source: folklore
 * Description: Segment tree for maximum subarray sum. Each node stores max prefix sum, max suffix sum, 
 * max subarray sum, and total sum. All except total sum are $\ge 0$.
 * Time: $O(\log N)$
 * Status: tested
 */
#pragma once

struct Node {
	ll ans, suf, pref, sum;
	Node() : ans(0), suf(0), pref(0), sum(0) {}
	Node(ll val) {
		sum = val;
		ans = suf = pref = max(0LL, val);
	}
};

template <typename T>
struct SegTree {
	Node unit{};
	Node f(Node a, Node b) {
		Node ret;
		ret.sum = a.sum + b.sum;
		ret.pref = max(a.pref, a.sum + b.pref);
		ret.suf = max(b.suf, b.sum + a.suf);
		ret.ans = max({a.ans, b.ans, a.suf + b.pref});
		return ret;
	}
	vector<Node> s; int n;
	SegTree(const vector<T>& v) : s(4 * sz(v)), n(sz(v)) {
		if (n > 0) build(0, n - 1, 1, v);
	}
	void build(int l, int r, int u, const vector<T>& v) {
		if (l == r) s[u] = Node(v[l]);
		else {
			int mid = (l + r) / 2;
			build(l, mid, 2 * u, v);
			build(mid + 1, r, 2 * u + 1, v);
			s[u] = f(s[2 * u], s[2 * u + 1]);
		}
	}
	void update(int idx, T val, int l, int r, int u) {
		if (l == r) s[u] = Node(val);
		else {
			int mid = (l + r) / 2;
			if (idx <= mid) update(idx, val, l, mid, 2 * u);
			else update(idx, val, mid + 1, r, 2 * u + 1);
			s[u] = f(s[2 * u], s[2 * u + 1]);
		}
	}
	Node query(int ql, int qr, int l, int r, int u) {
		if (ql > r || qr < l) return unit;
		if (l >= ql && r <= qr) return s[u];
		int mid = (l + r) / 2;
		return f(query(ql, qr, l, mid, 2 * u),
				 query(ql, qr, mid + 1, r, 2 * u + 1));
	}
	void update(int idx, T val) {
		update(idx, val, 0, n - 1, 1);
	}
	ll query(int l, int r) {
		if (l > r) return 0;
		return query(l, r, 0, n - 1, 1).ans;
	}
};
