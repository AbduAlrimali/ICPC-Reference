/**
 * Author: Competitive Programming Template
 * Date: 2026-07-21
 * License: CC0
 * Source: Folklore
 * Description: 2D Sparse Table for idempotent operations (GCD, min, max) on rectangular 0-indexed subgrids.
 * Usage:
 * Sparse2D<ll> st(grid);
 * ll ans = st.query(r1, c1, r2, c2); // inclusive bounds [r1..r2] x [c1..c2]
 * Time: O(N * M * log N * log M) build, O(1) query.
 * Status: tested
 */
#pragma once

template<class T = long long>
struct Sparse2D { // 0-indexed, rectangular subgrid queries
    int n, m;
    vector<int> lg2;
    vector<vector<vector<vector<T>>>> st;

    T combine(T a, T b) {return gcd(a, b); }

    Sparse2D(const vector<vector<T>> &z) : n(sz(z)), m(sz(z[0])) {
        int lim = max(n, m);
        lg2.resize(lim + 1);
        for (int i = 2; i <= lim; i++) lg2[i] = lg2[i >> 1] + 1;

        int LG1 = lg2[n] + 1;
        int LG2 = lg2[m] + 1;
        st.assign(n, vector<vector<vector<T>>>(m, vector<vector<T>>(LG1, vector<T>(LG2))));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                st[i][j][0][0] = z[i][j];
            }
        }

        for (int a = 0; a < LG1; a++) {
            for (int b = 0; b < LG2; b++) {
                if (a + b == 0) continue;
                for (int i = 0; i + (1 << a) <= n; i++) {
                    for (int j = 0; j + (1 << b) <= m; j++) {
                        if (!a) {
                            st[i][j][a][b] = combine(st[i][j][a][b - 1], st[i][j + (1 << (b - 1))][a][b - 1]);
                        } else {
                            st[i][j][a][b] = combine(st[i][j][a - 1][b], st[i + (1 << (a - 1))][j][a - 1][b]);
                        }
                    }
                }
            }
        }
    }

    T query(int x1, int y1, int x2, int y2) {
        x2++; y2++;
        int a = lg2[x2 - x1], b = lg2[y2 - y1];
        return combine(
            combine(st[x1][y1][a][b], st[x2 - (1 << a)][y1][a][b]),
            combine(st[x1][y2 - (1 << b)][a][b], st[x2 - (1 << a)][y2 - (1 << b)][a][b])
        );
    }
};
