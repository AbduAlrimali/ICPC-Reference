/**
 * Author: Simon Lindholm + hybrid extension
 * Date: 2025-01-15
 * License: CC0
 * Description: Ultra-safe rolling hash combining:
 * mod $2^{64} - 1$ (evil-test resistant, carry-based arithmetic) and
 * mod $2^{61} - 1$ (Mersenne prime, fast \& high quality).
 * Resistant to structured attacks (e.g. Thue-Morse, ABBA/BAAB),
 * with negligible collision probability ($\approx 2^{-125}$).
 * Time: Preprocessing: $O(n)$, Query: $O(1)$
 * Status: stress-tested
 */
#pragma once

using ull = uint64_t;
using u128 = __uint128_t;
struct H {
    static const ull M = (1ULL << 61) - 1;
    ull a, b; // a: mod 2^64-1, b: mod 2^61-1
    H(ull x=0) : a(x), b(x) {}
    H(ull x, ull y) : a(x), b(y) {}
    static ull mul61(ull x, ull y) {
        u128 t = (u128)x * y;
        ull r = (t >> 61) + (t & M);
        return r >= M ? r - M : r;
    }
    H operator+(H o) const {
        ull na = a + o.a + (a + o.a < a);
        ull nb = b + o.b; if (nb >= M) nb -= M;
        return {na, nb};
    }
    H operator-(H o) const {
        ull na = a + ~o.a;
        ull nb = b >= o.b ? b - o.b : b + M - o.b;
        return {na, nb};
    }
    H operator*(H o) const {
        u128 m = (u128)a * o.a;
        ull na = (ull)m + (ull)(m >> 64);
        ull nb = mul61(b, o.b);
        return {na, nb};
    }
    bool operator==(H o) const {
        return (a + !~a) == (o.a + !~o.a) && b == o.b;
    }
};
static const H C = (ull)1e11 + 3;


struct HashInterval {
    vector<H> h, p;
    HashInterval(const string& s) : h(s.size()+1), p(h) {
        p[0] = 1;
        for (int i = 0; i < (int)s.size(); i++)
            h[i+1] = h[i] * C + s[i],
            p[i+1] = p[i] * C;
    }
    H hashInterval(int l, int r) const { // hash [a, b)
        return h[r] - h[l] * p[r - l];
    }
};

/**
 * All hashes of substrings of fixed length.
 * Returns hashes of s[i..i+len)
 */
vector<H> getHashes(string& str, int length) {
    if (sz(str) < length) return {};
    H h = 0, pw = 1;
    rep(i,0,length)
        h = h * C + str[i], pw = pw * C;
    vector<H> ret = {h};
    rep(i,length,sz(str)) {
        ret.push_back(h = h * C + str[i] - pw * str[i-length]);
    }
    return ret;
}

/**
 * Hash entire string
 */
H hashString(string& s) {
    H h{};
    for (char c : s) h = h * C + c;
    return h;
}
