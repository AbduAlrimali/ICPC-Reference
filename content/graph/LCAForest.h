/**
 * Author: user
 * Date: 2026-07-21
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a forest in $O(1)$.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCAForest {
	vi euler, depth, first;
	RMQ<pii> rmq;

	LCAForest(int n, const vector<vi>& adj) : first(n, -1), depth(n) {
		for (int i = 0; i < n; i++) {
			if (first[i] == -1) dfs(adj, i, -1, 0);
		}
		vector<pii> ret(sz(euler));
		for (int i = 0; i < sz(euler); i++) {
			ret[i] = {depth[euler[i]], euler[i]};
		}
		rmq = RMQ<pii>(ret);
	}
	LCAForest(const vector<vi>& adj) : LCAForest(sz(adj), adj) {}

	void dfs(const vector<vi>& adj, int u, int p, int d) {
		first[u] = sz(euler);
		euler.push_back(u);
		depth[u] = d;
		for (int v : adj[u]) {
			if (v != p) {
				dfs(adj, v, u, d + 1);
				euler.push_back(u);
			}
		}
	}

	int lca(int a, int b) {
		int l = first[a], r = first[b];
		if (l > r) swap(l, r);
		return rmq.query(l, r + 1).second;
	}

	int dist(int a, int b) {
		return depth[a] + depth[b] - 2 * depth[lca(a, b)];
	}
};
