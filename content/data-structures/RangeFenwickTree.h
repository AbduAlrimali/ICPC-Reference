/**
 * Author: User
 * Date: 2025-01-14
 * License: CC0
 * Source: Folklore
 * Description: Fenwick Tree supporting Range Updates and Range Queries.
 * \texttt{update(l, r, v)} adds \texttt{v} to all elements in $[l, r]$.
 * \texttt{query(l, r)} returns the sum of elements in $[l, r]$.
 * 0-indexed.
 * Time: $O(\log N)$
 * Status: Tested
 */
#pragma once

struct RangeFT {
    vector<ll> b1, b2;
    RangeFT(int n) : b1(n), b2(n) {}
    void add(vector<ll>& b, int i, ll v) {
        for (; i < sz(b); i |= i + 1) b[i] += v;
    }
    ll sum(vector<ll>& b, int i) { // sum [0, i)
        ll res = 0;
        for (; i > 0; i &= i - 1) res += b[i-1];
        return res;
    }
    void update(int l, int r, ll v) { // add v to [l, r]
        add(b1, l, v); add(b1, r + 1, -v);
        add(b2, l, l * v); add(b2, r + 1, -(r + 1) * v);
    }
    ll query(int i) { // sum [0, i)
        return sum(b1, i) * i - sum(b2, i);
    }
    ll query(int l, int r) { // sum [l, r]
        return query(r + 1) - query(l);
    }
};