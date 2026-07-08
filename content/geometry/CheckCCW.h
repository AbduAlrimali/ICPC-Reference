/**
 * Author: user
 * Description: Returns true if the polygon vertices are in strictly 
 * counter-clockwise order using the Shoelace formula (signed area).
 * Time: O(N)
 */
#pragma once
#include "Point.h"

template<class T>
bool isCounter(const vector<Point<T>>& p) {
    if (sz(p) < 3) return false;
    T a = p.back().cross(p[0]);
    rep(i, 0, sz(p) - 1) a += p[i].cross(p[i + 1]);
    return a > 0;
}