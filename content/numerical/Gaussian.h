/**
 * Author: common knowledge
 * Date: 2026-05-29
 * License: CC0
 * Description: Gaussian elimination with full pivoting.
 * Reduces the first $m$ columns of matrix $a$ to Row Echelon Form (REF) 
 * or Reduced Row Echelon Form (RREF).
 * Returns {rank, determinant of the $m \times m$ square submatrix}.
 * $p$ will store the column permutations if provided.
 * Time: $O(n \cdot m \cdot \max(n, m))$
 */
#pragma once

typedef vector<double> vd;
const double eps = 1e-12;
pair<int, double> gaussian(vector<vd>& a, int m, bool rref = true, vi* p = nullptr) {
	int n = sz(a), k = sz(a[0]), rank = 0;
	double det = 1;
	vi q(m); iota(all(q), 0);
	rep(i,0,m) {
		if (rank == n) break;
		int r = rank, c = i;
		rep(j,rank,n) rep(l,i,m)
			if (fabs(a[j][l]) > fabs(a[r][c])) r = j, c = l;
		if (fabs(a[r][c]) < eps) { det = 0; continue; }
		a[rank].swap(a[r]);
		rep(j,0,n) swap(a[j][i], a[j][c]);
		swap(q[i], q[c]);
		if (r != rank) det = -det;
		if (c != i) det = -det;
		det *= a[rank][i];
		double v = a[rank][i];
		rep(j,i,k) a[rank][j] /= v;
		rep(j,0,n) if (j != rank && (rref || j > rank)) {
			double f = a[j][i];
			rep(l,i,k) a[j][l] -= f * a[rank][l];
		}
		rank++;
	}
	if (p) *p = q;
	return {rank, det};
}
