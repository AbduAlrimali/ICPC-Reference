/**
 * Author: Unknown
 * Date: 2026-07-18
 * License: CC0
 * Source: Lengauer-Tarjan
 * Description: Computes the Dominator Tree for a directed graph (handles both general graphs and DAGs) from a given root.
 * Time: O((V + E) \log V)
 * Usage:
 *  DominatorTree DT(n, root, adj);
 *  DT.idom[u] // Returns the immediate dominator of u (-1 if unreachable)
 *  DT.tree[u] // Returns a vector of nodes immediately dominated by u
 */
#pragma once

struct DominatorTree {
    int timer = 0;
    vector<vi> tree, radj, bucket;
    vi idom, sdom, par, dsu, label, id, rev, dom;
    int find(int u, int x = 0) {
        if (u == dsu[u]) return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if (v < 0) return u;
        if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
        return dsu[u] = v, x ? v : label[u];
    }
    void dfs(int u, const vector<vi>& g) {
        id[u] = ++timer;
        label[timer] = sdom[timer] = dsu[timer] = timer;
        rev[timer] = u;
        for (int v : g[u]) {
            if (!id[v]) dfs(v, g), par[id[v]] = id[u];
            radj[id[v]].push_back(id[u]);
        }
    }
    DominatorTree(int n, int root, const vector<vi>& g) : 
        tree(n), radj(n+1), bucket(n+1), idom(n, -1), sdom(n+1), par(n+1), 
        dsu(n+1), label(n+1), id(n, 0), rev(n+1), dom(n+1) {
        dfs(root, g);
        for (int i = timer; i >= 1; i--) {
            for (int p : radj[i]) sdom[i] = min(sdom[i], sdom[find(p)]);
            if (i > 1) bucket[sdom[i]].push_back(i);
            for (int w : bucket[i]) dom[w] = (sdom[find(w)] == sdom[w] ? sdom[w] : find(w));
            if (i > 1) dsu[i] = par[i];
        }
        for (int i = 2; i <= timer; i++) {
            if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
            tree[idom[rev[i]] = rev[dom[i]]].push_back(rev[i]);
        }
        if (timer > 0) idom[root] = root;
    }
};
