/**
 * Author: 
 * Date: 2026-06-26
 * License: CC0
 * Source: Own work
 * Description: N-dimensional Zobrist/Multiset Hashing struct. Assigns a unique 
 * N-tuple of random integers to elements to probabilistically verify multiset 
 * equality, permutation matching, or subarray compositions. Supports commutative 
 * merging via addition, removal via subtraction, and parity tracking via XOR.
 * Status: partially tested
 */
#pragma once

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
ll rand(ll l, ll r) return uniform_int_distribution<ll>(l, r)(rng);

template <size_t N = 5>
struct PermHash {
    array<ll, N> h;
    PermHash() { h.fill(0); }
    static PermHash random() {
        PermHash res;
        for (size_t i = 0; i < N; ++i) res.h[i] = rand(1, 1e9); // Replace with your RNG
        return res;
    }
    PermHash operator+(const PermHash& o) const {
        PermHash res;
        for (size_t i = 0; i < N; ++i) res.h[i] = h[i] + o.h[i];
        return res;
    }
    PermHash operator-(const PermHash& o) const {
        PermHash res;
        for (size_t i = 0; i < N; ++i) res.h[i] = h[i] - o.h[i];
        return res;
    }
    PermHash operator^(const PermHash& o) const {
        PermHash res;
        for (size_t i = 0; i < N; ++i) res.h[i] = h[i] ^ o.h[i];
        return res;
    }
    bool isEmpty() const {
        for (size_t i = 0; i < N; ++i) if (h[i]) return false;
        return true;
    }
    bool operator==(const PermHash& o) const { return h == o.h; }
};