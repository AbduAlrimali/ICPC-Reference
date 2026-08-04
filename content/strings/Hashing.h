/**
 * Author: AbduAlrimali
 * Date: 2026-07-21
 * Description: Unified Rolling Hash. Supports static range queries via build() and get(l, r), 
 * as well as O(1) dynamic sliding window operations (add/remove front/back).
 * Dynamic operations update the 'hash' and 'len' state, independent of the 'h' array.
 * Time: O(N) build, O(1) updates and queries.
 */
#pragma once


// H1(n, 131, 1e9+7)
// H2(n, 137, 1e9+9)
struct RollingHash {
    ll BASE, MODH, invBASE, hash, len;
    vl p, h;
    RollingHash(int sz, ll B, ll M) : p(sz + 1), h(sz + 1), BASE(B), MODH(M) {
        hash = len = 0;
        p[0] = 1;
        for (int i = 1; i <= sz; i++) {
            p[i] = (p[i - 1] * BASE) % MODH;
        }
        invBASE = modpow(BASE, MODH - 2, MODH);
    }
    static ll modpow(ll a, ll e, ll m) {
        ll r = 1;
        while (e) {
            if (e & 1) r = r * a % m;
            a = a * a % m;
            e >>= 1;
        }
        return r;
    }
    void build(const string &s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            h[i + 1] = (h[i] * BASE + s[i]) % MODH;
        }
        hash = h[n];
        len = n;
    }
    ll get(int l, int r) {
        ll res = (h[r + 1] - h[l] * p[r - l + 1]) % MODH;
        return (res + MODH) % MODH;
    }
    // Dynamic sliding window operations
    void add_back(char c) {
        hash = (hash * BASE + c) % MODH;
        len++;
    }
    void add_front(char c) {
        hash = (hash + c * p[len] % MODH) % MODH;
        len++;
    }
    void remove_back(char c) {
        hash = (hash - c + MODH) % MODH;
        hash = (hash * invBASE) % MODH;
        len--;
    }
    void remove_front(char c) {
        hash = (hash - c * p[len - 1] % MODH + MODH) % MODH;
        len--;
    }
};