/**
 * Author: User
 * Date: 2025-01-15
 * Description: Segmented Sieve for Primes, Phi, Mu, and Tau (Divisor Count).
 * Computes values for $[L, R]$ using precomputed small primes.
 * rem[i] > 1 after processing indicates a prime factor > sqrt(R).
 * Usage:
 * 1. Linear sieve primes up to $\sqrt{R_{MAX}}$.
 * 2. Set LIM $\ge$ max range length ($R - L + 1$).
 * 3. segSieve (Primes), segPhi (Totient), segMu (Mobius), segTau (Divisors).
 * Time: $O((R - L) \log \log R + \sqrt{R})$
 * Status: works
 */
#pragma once

const int LIM = 1e6+5; 
vector<ll> primes; // populate first
ll rem[LIM];
vector<bool> segSieve(ll L, ll R) {
	ll lim = sqrt(R);
	vector<bool> isP(R - L + 1, 1);
	if (L == 1) isP[0] = 0;
	for (ll p : primes) {
		if (p > lim) break;
		for (ll j = max(p * p, (L + p - 1) / p * p); j <= R; j += p)
			isP[j - L] = 0;
	}
	return isP;
}

ll phi[LIM];
void segPhi(ll L, ll R) {
    ll n = R - L + 1;
    iota(phi, phi + n, L);
    iota(rem, rem + n, L);
    for (ll p : primes) {
        if (p * p > R) break; 
        ll start = (L + p - 1) / p * p;
        for (ll i = max(start, p * p) - L; i < n; i += p) {
            phi[i] -= phi[i] / p;
            while (rem[i] % p == 0) rem[i] /= p;
        }
    }
    rep(i, 0, n) 
        if (rem[i] > 1) phi[i] -= phi[i] / rem[i];
}

int mu[LIM];
void segMu(ll L, ll R) {
    int n = R - L + 1;
    fill(mu, mu + n, 1); 
    iota(rem, rem + n, L);
    for (ll p : primes) {
        if (p * p > R) break;
        // Start at first multiple of p in range [L, R]
        for (ll i = (L + p - 1) / p * p - L; i < n; i += p) {
            if (rem[i] % p == 0) { // Optimization: check before expensive division loop
                int e = 0;
                while (rem[i] % p == 0) rem[i] /= p, e++;
                if (e > 1) mu[i] = 0;
                else if (mu[i]) mu[i] = -mu[i];
            }
        }
    }
    rep(i, 0, n) 
        if (rem[i] > 1 && mu[i]) mu[i] = -mu[i];
}

ll tau[LIM];
void segTau(ll L, ll R) {
    int n = R - L + 1;
    fill(tau, tau + n, 1);
    iota(rem, rem + n, L);

    for (ll p : primes) {
        if (p * p > R) break;
        for (ll i = (L + p - 1) / p * p - L; i < n; i += p) {
            int e = 0;
            while (rem[i] % p == 0) rem[i] /= p, e++;
            if (e) tau[i] *= (e + 1);
        }
    }
    rep(i, 0, n) 
        if (rem[i] > 1) tau[i] *= 2;
}