/**
 * Author: User
 * Date: 2026-06-05
 * License: CC0
 * Source: user
 * Description: Legendre's Formula. Finds the largest $x$ such that $k^x \mid n!$ where $k$ is prime.
 * For composite $k = k_1^{p_1} \dots k_m^{p_m}$, let $a_i$ be the count of $k_i$ in $n!$.
 * The answer for composite $k$ is $\min_i \lfloor a_i / p_i \rfloor$.
 * Time: $O(\log_k n)$
 * Status: unknown
 */
#pragma once

ll fact_pow(ll n, ll k) {
	ll res = 0;
	while (n) {
		n /= k;
		res += n;
	}
	return res;
}
