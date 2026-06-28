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
    int sz = 0;
    bool add(ll x) {
        for(int i=61; i>=0; i--) if(x >> i & 1)
            if(b[i]) x ^= b[i]; else return b[i] = x, sz++, true;
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
    ll kth(ll k) {
        if (k < 1 || k > (1LL << sz)) return -1;
        ll x = 0, cnt = 1LL << sz;
        for (int i=61; i>=0; i--) if (b[i]) {
            cnt >>= 1;
            bool want = k > cnt;
            if (want) k -= cnt;
            if (((x >> i) & 1) != want) x ^= b[i];
        }
        return x;
    }
    ll count_lt(ll x) {
        if (x < 0) return 0;
        ll ans = 0, mask = 0, cnt = 1LL << sz;
        for (int i=61; i>=0; i--) {
            if (b[i]) {
                cnt >>= 1;
                bool want = x >> i & 1;
                if (want) ans += cnt;
                if (((mask >> i) & 1) != want) mask ^= b[i];
            } else if (((x ^ mask) >> i) & 1) {
                return ans + ((x >> i & 1) ? cnt : 0);
            }
        }
        return ans;
    }
};