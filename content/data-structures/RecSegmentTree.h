/**
 * Author: User
 * Date: 2026-01-13
 * Description: Recursive Segment Tree.
 * Supports point update and range queries on [l, r] (inclusive).
 * Generic implementation: change 'T', 'unit', and 'f' for different operations.
 * Time: $O(N)$ build, $O(\log N)$ update/query.
 */
#pragma once

template <typename T>
struct SegTree {
    static constexpr T unit = 0;
    T f(T a, T b) { return a + b; } // (associative fn)
    vector<T> s; int n;
    SegTree(const vector<T>& v) : s(4*sz(v)), n(sz(v)) { 
        build(0, n-1, 1, v); 
    }
    void build(int l, int r, int u, const vector<T>& v) {
        if (l == r) s[u] = v[l];
        else {
            int mid = (l + r) / 2;
            build(l, mid, 2 * u, v);
            build(mid + 1, r, 2 * u + 1, v);
            s[u] = f(s[2 * u], s[2 * u + 1]);
        }
    }
    void update(int idx, T val, int l, int r, int u) {
        if (l == r) s[u] = val;
        else {
            int mid = (l + r) / 2;
            if (idx <= mid) update(idx, val, l, mid, 2 * u);
            else update(idx, val, mid + 1, r, 2 * u + 1);
            s[u] = f(s[2 * u], s[2 * u + 1]);
        }
    }
    T query(int ql, int qr, int l, int r, int u) {
        if (ql > r || qr < l) return unit;
        if (l >= ql && r <= qr) return s[u];
        int mid = (l + r) / 2;
        return f(query(ql, qr, l, mid, 2 * u),
                 query(ql, qr, mid + 1, r, 2 * u + 1));
    }
    void update(int idx, T val) {
        update(idx, val, 0, n - 1, 1);
    }
    T query(int l, int r) {
        return query(l, r, 0, n - 1, 1);
    }
};