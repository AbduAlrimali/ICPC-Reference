/**
 * Author: Abdua, folklore
 * Date: 2026-05-30
 * License: CC0
 * Source: folklore
 * Description: Segment tree for range GCD with range additions. 
 * Based on the property $\gcd(a_l, \dots, a_r) = \gcd(a_l, \gcd_{i=l}^r(a_i-a_l))$.
 * Time: $O(\log N \cdot \log(\max A_i))$
 * Status: tested
 */
#pragma once

struct Node {
	ll first, g, lazy;
	bool has_lazy, empty;
	Node() : first(0), g(0), lazy(0), has_lazy(false), empty(true) {}
	Node(ll v) : first(v), g(0), lazy(0), has_lazy(false), empty(false) {}
	void apply(ll v) {
		if (!empty) first += v, lazy += v, has_lazy = true;
	}
};

struct RangeGCD {
	Node merge(const Node& a, const Node& b) {
		if (a.empty) return b;
		if (b.empty) return a;
		Node res; res.empty = false;
		res.first = a.first;
		res.g = __gcd(abs(a.g), __gcd(abs(b.g), abs(a.first - b.first)));
		return res;
	}
	int n;
	vector<Node> tree;
	RangeGCD(const vector<ll>& v) : n(sz(v)), tree(4 * n) {
		if (n > 0) build(1, 0, n - 1, v);
	}
	void build(int u, int l, int r, const vector<ll>& v) {
		if (l == r) { tree[u] = Node(v[l]); return; }
		int mid = (l + r) / 2;
		build(2 * u, l, mid, v);
		build(2 * u + 1, mid + 1, r, v);
		tree[u] = merge(tree[2 * u], tree[2 * u + 1]);
	}
	void push(int u) {
		if (tree[u].has_lazy) {
			tree[2 * u].apply(tree[u].lazy);
			tree[2 * u + 1].apply(tree[u].lazy);
			tree[u].lazy = 0; tree[u].has_lazy = false;
		}
	}
	void update(int ql, int qr, ll v, int u, int l, int r) {
		if (ql <= l && r <= qr) { tree[u].apply(v); return; }
		push(u);
		int mid = (l + r) / 2;
		if (ql <= mid) update(ql, qr, v, 2 * u, l, mid);
		if (qr > mid) update(ql, qr, v, 2 * u + 1, mid + 1, r);
		tree[u] = merge(tree[2 * u], tree[2 * u + 1]);
	}
	Node query(int ql, int qr, int u, int l, int r) {
		if (ql <= l && r <= qr) return tree[u];
		push(u);
		int mid = (l + r) / 2;
		if (qr <= mid) return query(ql, qr, 2 * u, l, mid);
		if (ql > mid) return query(ql, qr, 2 * u + 1, mid + 1, r);
		return merge(query(ql, qr, 2 * u, l, mid),
		             query(ql, qr, 2 * u + 1, mid + 1, r));
	}
	void add(int l, int r, ll v) { if (l <= r) update(l, r, v, 1, 0, n - 1); }
	ll query(int l, int r) {
		if (l > r) return 0;
		Node res = query(l, r, 1, 0, n - 1);
		return __gcd(abs(res.first), abs(res.g));
	}
};
