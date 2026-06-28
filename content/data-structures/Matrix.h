/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Basic operations on matrices.
 * Usage: Matrix<int, 3> A; // Square 3x3
 *  Matrix<int, 3, 2> B; // Rectangular 3x2
 *  A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
 *  array<int, 3> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
#pragma once

template<class T, int N, int M = N> struct Matrix {
	array<array<T, M>, N> d{};
	template<int P>
	Matrix<T, N, P> operator*(const Matrix<T, M, P>& m) const {
		Matrix<T, N, P> a;
		rep(i,0,N) rep(k,0,M) rep(j,0,P) {
                a.d[i][j] += d[i][k] * m.d[k][j] % MOD;
                if(a.d[i][j]>=MOD) a.d[i][j] -= MOD;
            }
		return a;
	}
	array<T, N> operator*(const array<T, M>& vec) const {
		array<T, N> ret{};
		rep(i,0,N) rep(j,0,M) {
            ret[i] += d[i][j] * vec[j] % MOD;
            if(ret[i]>=MOD) ret[i] -= MOD;
        }
		return ret;
	}
	Matrix operator^(ll p) const {
		static_assert(N == M, "Exponentiation requires square matrix");
		assert(p >= 0);
		Matrix a, b(*this);
		rep(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};
