/**
 * Author: User
 * Date: 2025-01-13
 * License: CC0
 * Source: Folklore
 * Description: "Sack" or DSU on Trees. Solves offline subtree queries.
 * `val[u]` stores node values. `dfs` populates `ans`.
 * The heavy child is lazily kept; light children are brute-forced.
 * Fills `add` with problem specific logic.
 * Time: $O(N \log N)$
 * Status: Tested
 */
#pragma once

struct Sack {
    int n;
    vector<vi> adj;
    vi size, st, en, nodeAt;
    int timer;
    // Problem specific data
    vi val;
    Sack(int n) : n(n), adj(n), size(n), st(n), en(n), nodeAt(n), val(n), timer(0) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void prepare(int u, int p) {
        size[u] = 1;
        st[u] = timer; nodeAt[timer++] = u;
        for (auto &v : adj[u]) if (v != p) {
            prepare(v, u);
            size[u] += size[v];
            // Swap heavy child to front
            if (size[v] > size[adj[u][0]] || adj[u][0] == p) swap(v, adj[u][0]);
        }
        en[u] = timer;
    }
    void update(int u, int dir) {
        // dir = 1 (add), -1 (remove)
    }
    void dfs(int u, int p, bool keep) {
        int big = (adj[u].size() && adj[u][0] != p) ? adj[u][0] : -1;
        for (int v : adj[u]) 
            if (v != p && v != big) dfs(v, u, 0);
        if (big != -1) dfs(big, u, 1);
        for (auto v : adj[u]) {
            if (v != p && v != big) {
                rep(t, st[v], en[v]) update(nodeAt[t], 1);
            }
        }
        update(u, 1);

        // Answer query for u
        // ans[u] = ...

        if (!keep) {
            rep(t, st[u], en[u]) update(nodeAt[t], -1);
        }
    }
};