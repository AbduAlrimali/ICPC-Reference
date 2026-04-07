/**
 * Author: Unknown
 * Description: Computes $\binom{n}{r} \pmod p$ for large $n, r$ and small prime $p$.
 * The formula is $\binom{n}{r} \equiv \prod \binom{n_i}{r_i} \pmod p$ where $n_i, r_i$ are digits in base $p$.
 * Useful when $n \ge p$. Requires a standard `nCr` function for small inputs ($n < p$).
 * $p$ must be prime.
 * Time: O(\log_p n)
 * Status: Tested
 */
#pragma once

ll lucas(ll n, ll r, ll p) {
	if (r == 0) return 1;
	return lucas(n / p, r / p, p) * nCr(n % p, r % p) % p;
}