/**
 * Author: User
 * Date: 2026-06-05
 * Description: Given $f$ and $g$, computes $h[k] = \sum_{i \cup j = k, i \cap j = \emptyset} f[i]g[j]$.
 * Time: O(n^2 2^n) where $n$ is the number of bits.
 * Status: unknown
 */
#pragma once

const ll MOD = 998244353; // Or whatever the problem requires

void or_transform(vector<ll>& a, bool inv) {
    int n = sz(a);
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                if (!inv) {
                    a[i + len + j] += a[i + j];
                    if (a[i + len + j] >= MOD) a[i + len + j] -= MOD;
                } else {
                    a[i + len + j] -= a[i + j];
                    if (a[i + len + j] < 0) a[i + len + j] += MOD;
                }
            }
        }
    }
}

vector<ll> subset_conv(const vector<ll>& f, const vector<ll>& g, int n) {
    int N = 1 << n;
    vector<vector<ll>> fa(n + 1, vector<ll>(N, 0)), ga(n + 1, vector<ll>(N, 0));
    rep(i, 0, N) {
        fa[__builtin_popcount(i)][i] = f[i] % MOD;
        ga[__builtin_popcount(i)][i] = g[i] % MOD;
    }
    rep(i, 0, n + 1) {
        or_transform(fa[i], false);
        or_transform(ga[i], false);
    }
    vector<vector<ll>> ha(n + 1, vector<ll>(N, 0));
    rep(i, 0, n + 1) rep(j, 0, n + 1 - i) rep(mask, 0, N) 
            ha[i + j][mask] = (ha[i + j][mask] + fa[i][mask] * ga[j][mask]) % MOD;
    rep(i, 0, n + 1) or_transform(ha[i], true);
    vector<ll> h(N);
    rep(i, 0, N) h[i] = ha[__builtin_popcount(i)][i];
    return h;
}
