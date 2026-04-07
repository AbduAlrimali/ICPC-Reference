/**
 * Author: Unknown
 * Date: 2026-01-13
 * Source: Codeforces Blog
 * Description: Mo's Algorithm using Hilbert Curve order.
 * This improves cache locality and reduces the total pointer movement cost compared to standard block sorting.
 * No block size constant is needed.
 * Time: $O(N \sqrt{Q})$ for processing, sorting is $O(Q \log Q \cdot \log N)$.
 */
#pragma once

inline int64_t hilbert(int x, int y) {
    int64_t d = 0;
    for (int s = 1 << 20; s; s >>= 1) { // 1<<20 covers N <= 10^6
        bool rx = x & s, ry = y & s;
        d += s * 1LL * s * ((3 * rx) ^ ry);
        if (ry) continue;
        if (rx) x = ~x, y = ~y;
        swap(x, y);
    }
    return d;
}

vi mo(vector<pii> Q) {
    int L = 0, R = 0;
    vi s(sz(Q)), res = s;
    iota(all(s), 0);
    sort(all(s), [&](int a, int b) {
        return hilbert(Q[a].first, Q[a].second) < hilbert(Q[b].first, Q[b].second);
    });
    for (int qi : s) {
        pii q = Q[qi];
        while (L > q.first) add(--L, 0);
        while (R < q.second) add(R++, 1);
        while (L < q.first) del(L++, 0);
        while (R > q.second) del(--R, 1);
        res[qi] = calc();
    }
    return res;
}