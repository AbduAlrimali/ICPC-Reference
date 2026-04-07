/**
 * Author: Unknown
 * Description: Finds a primitive root modulo $p$.
 * Time: O(ans \cdot \log \phi(p) \cdot \log p)
 */
#pragma once
#include "ModPow.h"

ll primitiveRoot(ll p) {
	if (p == 2) return 1;
	vector<ll> factors = factor(p - 1); // Get prime factors of p-1
	for (ll g = 2; ; ++g) {
		bool ok = 1;
		for (auto f : factors)
			if (modpow(g, (p - 1) / f.first, p) == 1) { ok = 0; break; }
		if (ok) return g;
	}
}