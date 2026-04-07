/**
 * Author: Unknown
 * Description: Solves $ax \equiv b \pmod n$.
 * Returns $\{x_0, m\}$ such that the general solution is $x \equiv x_0 \pmod m$.
 * To get all solutions in $[0, n)$: $x_k = x_0 + k \cdot m$ for $k \in [0, \gcd(a, n))$.
 * Requires `euclid` which returns $\{g, x, y\}$.
 * Time: $O(\log n)$
 */
#pragma once
#include "Euclid.h"

pair<ll, ll> linearCong(ll a, ll b, ll n) {
    ll x, y, g = euclid(a, n, x, y);
    ll m = n / g;
    if (b % g) return {-1, -1};
    x = (x % m + m) % m; // Normalize x
    return {(x * (b / g)) % m, m};
}