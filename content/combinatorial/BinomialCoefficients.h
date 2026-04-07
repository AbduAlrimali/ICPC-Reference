/**
 * Author: Unknown
 * Description: Modular combinations and permutations. 
 * Precomputes factorials and inverses in linear time.
 * Time: O(N) init, O(1) query.
 */
#pragma once

struct BinomialCoefficients {
	ll n, mod;
	vector<ll> fact, inv, finv;
	BinomialCoefficients(ll n, ll mod) : n(n), mod(mod), fact(n), inv(n), finv(n) {
		fact[0] = inv[1] = finv[0] = 1;
		for (int i = 1; i < n; i++) {
			fact[i] = fact[i - 1] * i % mod;
			if (i > 1) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
			finv[i] = finv[i - 1] * inv[i] % mod;
		}
	}
	ll nPr(ll n, ll r){ return (n<r||r<0) ? 0:1LL * fact[n] * finv[n-r] % mod; }
    ll nCr(ll n, ll r){ return 1LL * nPr(n, r) * finv[r] % mod; }
};