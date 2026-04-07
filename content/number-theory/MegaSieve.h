/**
 * Author: Unknown
 * Description: Linear Sieve. Computes multiplicative functions for all numbers up to $N$.
 * $\mu$ (Mobius), $\phi$ (Euler totient), $num$ (number of divisors), and $sig$ (sum of divisors).
 * $cnt[i]$ stores the exponent of the smallest prime factor of $i$, and $sp[i]$ stores the sum of the geometric series of that prime factor.
 * Time: $O(N)$
 */
#pragma once

const int N = 1e7+5;
int primes[N], k, mu[N], phi[N], num[N], sig[N], cnt[N], sp[N];
bitset<N> vis;

void megasieve() {
	mu[1] = phi[1] = num[1] = sig[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!vis[i]) primes[k++] = i, mu[i] = -1, phi[i] = i-1, num[i] = 2, sig[i] = sp[i] = i+1, cnt[i] = 1;
		for (int j = 0, P, x; j < k && (x = i * (P=primes[j])) < N; ++j) {
			vis[x] = 1;
			if (i % P) {
				mu[x] = -mu[i], phi[x] = phi[i] * (P - 1);
				cnt[x] = 1, num[x] = num[i] * 2;
				sp[x] = P + 1, sig[x] = sig[i] * sp[x];
			} else {
				mu[x] = 0, phi[x] = phi[i] * P;
				cnt[x] = cnt[i] + 1, num[x] = num[i] / (cnt[i] + 1) * (cnt[x] + 1);
				sp[x] = sp[i] * P + 1, sig[x] = sig[i] / sp[i] * sp[x];
				break;
			}
		}
	}
}