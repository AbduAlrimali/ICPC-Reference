/**
 * Author: Unknown
 * Date: 2026-07-25
 * License: CC0
 * Source: Unknown
 * Description: Implicit Persistent Segment Tree. Operates on a dynamic value range
 * [MIN\textunderscore VAL, MAX\textunderscore VAL] without coordinate compression.
 * reserve\_nodes = $N \times (\lceil \log_2(\text{MAX\textunderscore VAL} - \text{MIN\textunderscore VAL}) \rceil + 2)$
 * Time: O(\log(MAX - MIN)) per query/update.
 * Memory: O(N \log(MAX - MIN))
 * Status: unverified
 */
#pragma once

struct PSegTree {
	struct Node {
		ll val = 0;
		int l = 0, r = 0;
	};

	vector<Node> tree;
	vector<int> roots;
	ll MIN_VAL, MAX_VAL;

	PSegTree(ll min_v, ll max_v, int reserve_nodes = 0)
	    : MIN_VAL(min_v), MAX_VAL(max_v) {
		if (reserve_nodes > 0) tree.reserve((size_t)reserve_nodes);
		tree.push_back({}); // Index 0 is the universal null/empty node
		roots.push_back(0);
	}

	int update(int node, ll L, ll R, ll pos, ll val) {
		int cur = (int)tree.size();
		tree.push_back(tree[(size_t)node]);
		if (L == R) {
			tree[(size_t)cur].val += val; // Change to `=` if overwriting is preferred
			return cur;
		}
		ll mid = L + (R - L) / 2;
		if (pos <= mid) {
			tree[(size_t)cur].l = update(tree[(size_t)node].l, L, mid, pos, val);
		} else {
			tree[(size_t)cur].r = update(tree[(size_t)node].r, mid + 1, R, pos, val);
		}
		tree[(size_t)cur].val = tree[(size_t)tree[(size_t)cur].l].val + tree[(size_t)tree[(size_t)cur].r].val;
		return cur;
	}

	// Creates a new version of the tree based on an existing root
	int update(int root_idx, ll pos, ll val) {
		int new_root = update(roots[(size_t)root_idx], MIN_VAL, MAX_VAL, pos, val);
		roots.push_back(new_root);
		return new_root;
	}

	ll query(int node, ll L, ll R, ll ql, ll qr) {
		if (!node || L > qr || R < ql) return 0;
		if (ql <= L && R <= qr) return tree[(size_t)node].val;

		ll mid = L + (R - L) / 2;
		return query(tree[(size_t)node].l, L, mid, ql, qr) +
		       query(tree[(size_t)node].r, mid + 1, R, ql, qr);
	}

	// Queries a specific version of the tree
	ll query(int root_idx, ll ql, ll qr) {
		return query(roots[(size_t)root_idx], MIN_VAL, MAX_VAL, ql, qr);
	}
};
