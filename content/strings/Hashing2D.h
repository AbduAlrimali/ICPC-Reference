/**
 * Author: 
 * Date: 2026-07-21
 * Description: 2D Rolling Hash for grid pattern matching.
 * Utilizes two bases to maintain spatial integrity across rows and columns.
 * Supports O(1) subgrid hash queries via 2D prefix structures.
 * Time: O(R \times C) build, O(1) query.
 * Status: Tested
 */
#pragma once

// RollingHash2D H1(n, m, 313, 317, 1000000007)
// RollingHash2D H2(n, m, 337, 347, 1000000009)
struct RollingHash2D {
	ll BR, BC, MODH;
	vector<vector<ll>> h;
	vector<ll> pR, pC;

	RollingHash2D(int szR, int szC, ll BaseR, ll BaseC, ll M) 
		: pR(szR + 1), pC(szC + 1), h(szR + 1, vector<ll>(szC + 1, 0)), 
		  BR(BaseR), BC(BaseC), MODH(M) {
		
		pR[0] = 1;
		pC[0] = 1;
		rep(i, 1, szR + 1) pR[i] = (pR[i - 1] * BR) % MODH;
		rep(i, 1, szC + 1) pC[i] = (pC[i - 1] * BC) % MODH;
	}

	void build(const vector<string> &grid) {
		int R = sz(grid);
		int C = grid.empty() ? 0 : sz(grid[0]);
		
		rep(i, 1, R + 1) {
			rep(j, 1, C + 1) {
				ll val = grid[i - 1][j - 1];
				
				// 2D Hash Prefix Formula: 
				// h[i][j] = h[i-1][j]*BR + h[i][j-1]*BC - h[i-1][j-1]*BR*BC + val
				ll t1 = (h[i - 1][j] * BR) % MODH;
				ll t2 = (h[i][j - 1] * BC) % MODH;
				ll t3 = (h[i - 1][j - 1] * BR) % MODH * BC % MODH;
				
				h[i][j] = (t1 + t2 - t3 + val) % MODH;
				if (h[i][j] < 0) h[i][j] += MODH;
			}
		}
	}

	// Queries the hash of the subgrid from (r1, c1) to (r2, c2) inclusive (0-indexed)
	ll get(int r1, int c1, int r2, int c2) {
		r1++; c1++; r2++; c2++;
		
		ll term1 = h[r2][c2];
		ll term2 = h[r1 - 1][c2] * pR[r2 - r1 + 1] % MODH;
		ll term3 = h[r2][c1 - 1] * pC[c2 - c1 + 1] % MODH;
		ll term4 = h[r1 - 1][c1 - 1] * pR[r2 - r1 + 1] % MODH * pC[c2 - c1 + 1] % MODH;
		
		ll res = term1 - term2 - term3 + term4;
		return (res % MODH + MODH) % MODH;
	}
};
