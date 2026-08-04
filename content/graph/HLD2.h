/**
 * Author: Unknown
 * Date: 2026-07-29
 * License: CC0
 * Description: Heavy-Light Decomposition. Supports path query decomposition.
 * Time: O(\log N) per path query
 * Status: tested
 */
#pragma once

struct HLD {
	vi big, head, siz, parent, id, depth;
	int nxt, edge_based, root;
	HLD(int n, vector<vi> &adj, int r, int e=0)
		: big(n+1, -1), head(n+1), siz(n+1, 1), parent(n+1),
		  id(n+1), depth(n+1), edge_based(e), root(r) {
		nxt = 0;
		head[root] = root;
		dfs(root, adj);
		flatten(root, adj);
	}
	void dfs(int u, vector<vi> &adj) {
		for(int v : adj[u]) {
			if(v == parent[u]) continue;
			parent[v] = u;
			depth[v] = depth[u] + 1;
			dfs(v, adj);
			siz[u] += siz[v];
			if(big[u] == -1 || siz[v] > siz[big[u]]) {
				big[u] = v;
			}
		}
	}
	void flatten(int u, vector<vi> &adj) {
		id[u] = nxt++;
		if(big[u] != -1) {
			head[big[u]] = head[u];
			flatten(big[u], adj);
		}
		for(int v : adj[u]) {
			if(v == parent[u] || v == big[u]) continue;
			head[v] = v;
			flatten(v, adj);
		}
	}
	vector<pii> path(int u, int v) {
		vector<pii> res;
		while(true) {
			if(head[u] == head[v]) {
				if(depth[v] > depth[u]) {
					swap(u, v);
				}
				res.push_back({id[v] + edge_based, id[u]});
				return res;
			}
			if(depth[head[v]] > depth[head[u]]) {
				swap(u, v);
			}
			res.emplace_back(id[head[u]], id[u]);
			u = parent[head[u]];
		}
	}
};
