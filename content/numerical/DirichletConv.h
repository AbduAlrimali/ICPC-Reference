/**
 * Author: Folklore
 * Date: 2026-05-28
 * License: CC0
 * Source: Folklore
 * Description: In-place Dirichlet Convolution (is\_gcd=true for GCD, false for LCM).
 * Computes $c[k] = \sum a[i] * b[j] \pmod{MOD}$. 1-based indexing assumed.
 * Uses efficient addition/subtraction to avoid slow \% operators.
 * Time: $O(N \log N)$
 * Status: tested
 */
#pragma once

template<class T>
vector<T> dirichlet_conv(vector<T> a, vector<T> b, bool is_gcd, T mod) {
    int n = max(a.size(), b.size()) - 1;
    a.resize(n + 1); b.resize(n + 1);
    
    auto fwd = [&](vector<T>& v) {
        if (is_gcd) 
            for (int i = 1; i <= n; ++i) 
                for (int j = 2 * i; j <= n; j += i) { v[i] += v[j]; if (v[i] >= mod) v[i] -= mod; }
        else 
            for (int i = n; i >= 1; --i) 
                for (int j = 2 * i; j <= n; j += i) { v[j] += v[i]; if (v[j] >= mod) v[j] -= mod; }
    };
    
    fwd(a); fwd(b);
    for (int i = 1; i <= n; ++i) a[i] = 1LL * a[i] * b[i] % mod;
    
    if (is_gcd) 
        for (int i = n; i >= 1; --i) 
            for (int j = 2 * i; j <= n; j += i) { a[i] -= a[j]; if (a[i] < 0) a[i] += mod; }
    else
        for (int i = 1; i <= n; ++i) 
            for (int j = 2 * i; j <= n; j += i) { a[j] -= a[i]; if (a[j] < 0) a[j] += mod; }
    
    return a;
}