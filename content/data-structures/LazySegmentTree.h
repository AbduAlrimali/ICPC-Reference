/**
 * Author: User
 * Date: 2026-01-13
 * Description: Segment Tree with Lazy Propagation.
 * Time: $O(N)$ build, $O(\log N)$ update/query.
 * Status: Tested
 */
#pragma once

template <typename T>
struct LazySegTree {
    int n;
    vector<T> tree;
    vector<int> lazy;
    LazySegTree(const vector<T> &a) : n(a.size()), tree(4 * n), lazy(4 * n) {
        build(1, 0, n - 1, a);
    }
    T f(T a, T b) { return a + b; } // (associative fn)
    void build(int v, int l, int r, const vector<T> &a) {
        if (l == r) {
            tree[v] = a[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m + 1, r, a);
            tree[v] = f(tree[2 * v], tree[2 * v + 1]);
        }
    }
    void apply(int v, int len, int x) {
        tree[v] += x*len;
        lazy[v] += x;
    }
    void push(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = 0;
    }
    void update(int ql, int qr, int x, int v, int l, int r) {
        if (qr < l || ql > r) return;
        if (l >= ql && r <= qr) {
            apply(v, r - l + 1, x);
        } else {
            push(v, l, r);
            int m = (l + r) / 2;
            update(ql, qr, x, 2 * v, l, m);
            update(ql, qr, x, 2 * v + 1, m + 1, r);
            tree[v] = f(tree[2 * v], tree[2 * v + 1]);
        }
    }
    T query(int ql, int qr, int v, int l, int r) {
        if (qr < l || ql > r) return 0;
        if (l >= ql && r <= qr) return tree[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return f(query(ql, qr, 2 * v, l, m), query(ql, qr, 2 * v + 1, m + 1, r));
    }
    void update(int ql, int qr, int x) { update(ql, qr, x, 1, 0, n - 1); }
    T query(int ql, int qr) { return query(ql, qr, 1, 0, n - 1); }
};