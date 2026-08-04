/**
 * Author: abdua
 * Date: 2026-07-13
 * License: CC0
 * Source: folklore
 * Description: Generic Square Root Decomposition for point update and range query.
 * Easily adjustable for min, max, gcd, etc. Modify the neutral element and 
 * the combine operation where indicated.
 * Time: O(\sqrt{N})
 * Status: tested
 */
#pragma once

struct SqrtDecomp {
    static const int S = 450; // ~sqrt(N), adjust based on N (450 is good for 2e5)
    int n;
    vector<ll> a, b;

    SqrtDecomp(vector<ll> &z) : n(sz(z)), a(z), b(sz(z)/S+1) {
        for(int i=0;i<n;i++){
            b[i/S]+=a[i];
        }
    }
    
    // Default example is Range Sum. 
    void update(int p, ll val) {
        a[p] = val;
        int blk = p / S;
        b[blk] = 0; // 1. CHANGE HERE: Neutral element (e.g., INF for min, 0 for gcd)
        
        int start = blk * S;
        int end = min(start + S, n);
        rep(i, start, end) {
            b[blk] += a[i]; // 2. CHANGE HERE: Combine operation (e.g., min(b[blk], a[i]))
        }
    }

    ll query(int L, int R) {
        ll res = 0; // 3. CHANGE HERE: Neutral element
        int bL = L / S, bR = R / S;
        
        if (bL == bR) {
            rep(i, L, R + 1) res += a[i]; // 4. CHANGE HERE: Combine
        } else {
            rep(i, L, (bL + 1) * S) res += a[i]; // 4. CHANGE HERE: Combine
            rep(i, bL + 1, bR) res += b[i];      // 4. CHANGE HERE: Combine
            rep(i, bR * S, R + 1) res += a[i];   // 4. CHANGE HERE: Combine
        }
        return res;
    }
};
