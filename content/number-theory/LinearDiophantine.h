/**
 * Author: Unknown
 * Description: Solves the Diophantine equation $ax + by = c$. 
 * Stores the solution in $x$ and $y$ such that $ax + by = c$.
 * Returns false if no solution exists.
 * To get all solutions: $x = x0 + k \cdot \frac{b}{g}, \quad y = y0 - k \cdot \frac{a}{g}$.
 * Requires `euclid` (extended GCD).
 * Time: $O(\log(\min(a, b)))$
 */
#pragma once
#include "Euclid.h"

bool linearDiophantine(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
    if (!a && !b) return c == 0;
    ll x0, y0, gc = euclid(abs(a), abs(b), x0, y0); // |a|x0 + |b|y0 = g
    if (c % gc) return false;
    __int128 r = c / gc; 
    x = (ll)(r * x0 % (b / gc)); // Normalize x for small magnitude
    if (a < 0) x = -x;
    y = (c - a * x) / b;
    g=gc;
    return true;
}