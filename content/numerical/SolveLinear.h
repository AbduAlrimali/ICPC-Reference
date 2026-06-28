/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned.
 *  Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
 * Time: O(n^2 m)
 * Status: tested
 */
#pragma once

#include "Gaussian.h"

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x);
	rep(i,0,n) A[i].push_back(b[i]);
	vi p;
	auto res = gaussian(A, m, true, &p);
	x.assign(m, 0);
	rep(i,res.first,n) if (fabs(A[i][m]) > eps) return -1;
	rep(i,0,res.first) x[p[i]] = A[i][m];
	return res.first;
}
