/**
 * Author: User
 * Date: 2025-01-13
 * License: CC0
 * Source: Folklore
 * Description: Disjoint Set Union on ranges (Parallel DSU). 
 * Allows forcing two ranges [l1, r1] and [l2, r2] to be identical.
 * Constraints are lazily propagated down from larger power-of-2 segments to smaller ones.
 * After all unions, call \texttt{propagate()} to push everything to level 0.
 * \texttt{find(i, 0)} gives the component ID of index i.
 * Time: Construction $O(N \log N)$, Union $O(\alpha(N))$, Propagation $O(N \log N \alpha(N))$.
 * Status: Tested
 */
#pragma once

struct RangeDSU {
    int n;
    vector<vi> par;
    RangeDSU(int n) : n(n) {
        int k = __lg(n) + 1;
        par.assign(k, vi(n));
        for (int i = 0; i < k; i++) iota(all(par[i]), 0);
    }
    int find(int i, int k) { // lvl k
        return par[k][i] == i ? i : par[k][i] = find(par[k][i], k);
    }
    void join(int i, int j, int k) {
        i = find(i, k); j = find(j, k);
        if (i != j) par[k][i] = j;
    }
    // Force range s[l1...r1] == s[l2...r2]
    void join_range(int l1, int r1, int l2, int r2) {
        int len = r1 - l1 + 1;
        int k = __lg(len);
        join(l1, l2, k);
        join(r1 - (1 << k) + 1, r2 - (1 << k) + 1, k);
    }
    void propagate() {
        for (int i = par.size() - 1; i > 0; i--) {
            for (int j = 0; j <= n - (1 << i); j++) {
                int root = find(j, i);
                if (j != root) {
                    join(j, root, i - 1);
                    join(j + (1 << (i - 1)), root + (1 << (i - 1)), i - 1);
                }
            }
        }
    }
};