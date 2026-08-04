/**
 * Author: Unknown
 * Date: 2026-07-16
 * Description: Basic matrix multiplication and exponentiation modulo $mod$.
 * Time: $O(N^3)$ for multiplication, $O(N^3 \log b)$ for exponentiation.
 * Status: tested
 */
#pragma once

typedef vector<vector<ll>> Matrix;

Matrix mul(Matrix& a, Matrix& b, ll mod) {
	Matrix c(sz(a), vector<ll>(sz(b[0]), 0));
	rep(i,0,sz(a)) rep(j,0,sz(b[0])) rep(k,0,sz(b)) {
		c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
	}
	return c;
}

Matrix fastmat(Matrix a, ll b, ll mod) {
	Matrix res(sz(a), vector<ll>(sz(a[0]), 0));
	rep(i,0,sz(a)) res[i][i] = 1;
	while (b > 0) {
		if (b & 1) res = mul(res, a, mod);
		a = mul(a, a, mod);
		b >>= 1;
	}
	return res;
}
