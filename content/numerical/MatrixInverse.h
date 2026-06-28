/**
 * Author: Max Bennedich
 * Date: 2004-02-08
 * Description: Invert matrix $A$. Returns rank; result is stored in $A$ unless singular (rank < n).
 * Can easily be extended to prime moduli; for prime powers, repeatedly
 * set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Status: Slightly tested
 */
#pragma once

#include "Gaussian.h"

int matInv(vector<vd>& A) {
	int n = sz(A);
	rep(i,0,n) rep(j,0,n) A[i].push_back(i == j);
	vi p;
	auto res = gaussian(A, n, true, &p);
	if (res.first < n) return res.first;
	vector<vd> resA(n, vd(n));
	rep(i,0,n) rep(j,0,n) resA[p[i]][j] = A[i][n + j];
	A = resA;
	return n;
}
