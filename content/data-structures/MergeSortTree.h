/**
 * Author: User
 * Date: 2025-01-15
 * Description: Segment tree where each node holds a sorted vector of the range.
 * Useful for querying the number of elements $> V$ in range $[L, R]$.
 * Replace upper\_bound() with lower\_bound() to query $\ge v$.
 * Time: $O(N \log N)$ build, $O(\log^2 N)$ query.
 * Memory: $O(N \log N)$
 */
#pragma once

template <typename T>
struct MergeSortTree {
    int n;
    vector<vector<T>> tree;
    MergeSortTree(vector<T>& a) : n(sz(a)), tree(4*n) {
        build(1, 0, n-1, a);
    }
    void build(int node, int l, int r, vector<T>& a) {
        if (l == r) {
            tree[node] = {a[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(2*node, l, mid, a);
        build(2*node+1, mid+1, r, a);
        merge(all(tree[2*node]), all(tree[2*node+1]), back_inserter(tree[node]));
    }
    T query(int node, int tl, int tr, int l, int r, T v) {
        if (l > tr || r < tl) return 0;
        if (l <= tl && tr <= r) {
            return tree[node].end() - upper_bound(all(tree[node]), v);
        }
        int mid = (tl + tr) / 2;
        return query(2*node, tl, mid, l, r, v) + 
        query(2*node+1, mid+1, tr, l, r, v);
    }
    T query(int l, int r, T v) { // count of numbers in a[l..r] greater than v
        return query(1, 0, n-1, l, r, v);
    }
};