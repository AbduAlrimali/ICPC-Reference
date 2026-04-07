/**
 * Author: User
 * Date: 2025-01-13
 * License: CC0
 * Description: Coordinate Compression helper. 
 * `get(x)` returns the rank of value `x` (0-indexed).
 * `c[i]` returns the original value with rank `i`.
 * Time: Construction $O(N \log N)$, Query $O(\log N)$.
 * Status: Tested
 */
#pragma once

struct Compress {
    vector<ll> vals;
    Compress(vector<ll> &v) : vals(v) {
        sort(all(vals));
        vals.erase(unique(all(vals)), vals.end());
    }
    int get(ll x) { 
        return lower_bound(all(vals), x) - vals.begin(); 
    }
    ll operator[](int i) { return vals[i]; }
    int size() { return vals.size(); }
};