/**
 * Author: Unknown
 * Description: Counts non-negative integer solutions $(x, y)$ to $ax + by \le c$.
 * Equivalent to counting lattice points in the triangle bounded by axes and the line.
 * Requires `divsum`.
 * Time: O(\log(\min(a, b)))
 */
#pragma once
#include "ModSum.h"
 
ll lattice_cnt(ll a, ll b, ll c) {
	if (c < 0) return 0;
	if (a == 0 || b == 0) return -1;
	ll n = c / a;
	return divsum(n + 1, c % a, a, b) + n + 1;
}