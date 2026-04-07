/**
 * Author: User
 * Date: 2026-01-13
 * Description: Linear basis for XOR. 
 * 'add' returns true if x increased the basis size.
 * 'has' returns true if x can be formed by the basis.
 * Time: $O(bits)$
 */
#pragma once

struct Basis {
    ll b[62]{};
    bool add(ll x) {
        for(int i=61; i>=0; i--) if(x >> i & 1)
            if(b[i]) x ^= b[i]; else return b[i] = x, true;
        return false;
    }
    bool has(ll x) {
        for(int i=61; i>=0; i--) if(x >> i & 1) x ^= b[i];
        return !x;
    }
    ll query(ll x = 0) {
        for(int i=61; i>=0; i--) x = max(x, x ^ b[i]);
        return x;
    }
};