/**
 * Author: Unknown
 * Date: 2024-03-19
 * License: CC0
 * Source: custom
 * Description: Pointer-based dynamic segment tree with lazy propagation (range set).
 * Can use bump allocator for speed. Only creates nodes when necessary.
 * Time: $O(\log N)$ per update/query.
 * Usage: Tree* root = new Tree(0, 1e9);
 * Status: tested
 */
#pragma once

#include "../various/BumpAllocator.h"

struct Tree {
    Tree *l = 0, *r = 0;
    int lo, hi;
    ll sum = 0, lz = 0;
    bool has = 0; // is_lazy
    Tree(int L, int R) : lo(L), hi(R) {}

    void apply(ll v) { sum = (ll)(hi - lo) * v; lz = v; has = 1; }

    void push() {
        if (lo + 1 == hi || !has) return;
        int m = lo + (hi - lo) / 2;
        if (!l) l = new Tree(lo, m); if (!r) r = new Tree(m, hi);
        l->apply(lz); r->apply(lz);
        has = 0;
    }

    void update(int L, int R, ll v) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) return apply(v);
        push();
        int m = lo + (hi - lo) / 2;
        if (L < m) { if (!l) l = new Tree(lo, m); l->update(L, R, v); }
        if (R > m) { if (!r) r = new Tree(m, hi); r->update(L, R, v); }
        sum = (l ? l->sum : 0) + (r ? r->sum : 0);
    }

    ll query(int L, int R) {
        if (R <= lo || hi <= L) return 0;
        if (L <= lo && hi <= R) return sum;
        if (has) return (ll)(min(R, hi) - max(L, lo)) * lz;
        int m = lo + (hi - lo) / 2;
        return (l && L < m ? l->query(L, R) : 0) + (r && R > m ? r->query(L, R) : 0);
    }
};