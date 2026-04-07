/**
 * Author: Unknown
 * Description: Solves $x^k \equiv a \pmod p$ for prime $p$.
 * Returns one solution, or -1 if none exists.
 * Requires `modLog`, `primitiveRoot`, `linearCongruence`.
 * Time: O(\sqrt p)
 */
#pragma once
#include "PrimitiveRoot.h"
#include "LinearCong.h"
#include "modLog.h"

ll discreteRoot(ll k, ll a, ll p) {
	if (a == 0) return 0;
	ll g = primitiveRoot(p);
	// 1. Solve g^y = a (mod p) for y (Discrete Log)
	ll y = modLog(g, a, p);
	if (y == -1) return -1;
	// 2. Solve k * x = y (mod p-1) for x (Linear Congruence)
	auto res = linearCong(k, y, p - 1); // Returns {x0, m}
	if (res.first == -1) return -1;
	// 3. Result is g^x (mod p)
	return modpow(g, res.first, p);
}