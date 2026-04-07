/**
 * Author: Unknown
 * Description: Generate all divisors from a list of (prime, exponent).
 */
#pragma once

vector<ll> getDivisors(const vector<pll>& fact) {
    vector<ll> d = {1};
    for (auto [p, e] : fact)
        for (int i = 0, n = d.size(); i < n; ++i)
            for (ll v = d[i], j = 0; j < e; ++j) d.push_back(v *= p);
    return d;
}
