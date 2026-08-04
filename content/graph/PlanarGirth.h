/**
 * Author: Unknown
 * Date: 2026-07-26
 * Source: Euler's Formula
 * Description: Finds the girth of a planar graph with minimum degree $\ge 3$ using Euler's limit.
 * The girth of such a graph is at most 5.
 * $dir\_adj$ must orient undirected edges from lower degree to higher degree (out-degree bounded by 5).
 * Time: O(V)
 * Status: tested
 */
#pragma once

int planarGirth(int n, const vector<vi>& adj, const vector<vi>& dir_adj) {
	int ans = 5;
	vi mark(n + 1), common(n + 1);

	// C3 Verification
	for(int u = 1; u <= n; u++) {
		for(int v : adj[u]) mark[v] = u;
		for(int v : dir_adj[u]) {
			for(int w : dir_adj[v]) {
				if(mark[w] == u) ans = min(ans, 3);
			}
		}
	}

	// C4 Verification
	for(int u = 1; u <= n; u++) {
		for(int v : adj[u]) {
			for(int w : dir_adj[v]) {
				if(w == u) continue;
				if(common[w] == u) ans = min(ans, 4);
				else common[w] = u;
			}
		}
	}
	return ans;
}
