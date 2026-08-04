/**
 * Author: Unknown
 * Date: 2026-07-16
 * Description: SOS (Sum Over Subsets) DP / Fast Zeta Transform.
 * Forward Pass (Zeta): Build sums from original (use +=).
 * Backward Pass (Mobius): Invert to extract original (use -=).
 * Status: tested
 */
#pragma once

// Cheat Sheet (inside the if condition):
// Sum over Subsets (0 flows to 1):
//   dp[bit_on] += dp[bit_off]; // Subsets to Superset
// Undo Sum over Subsets:
//   dp[bit_on] -= dp[bit_off];
// Sum over Supersets (1 flows to 0):
//   dp[bit_off] += dp[bit_on]; // Supersets to Subset
// Undo Sum over Supersets:
//   dp[bit_off] -= dp[bit_on];

void sos(vector<ll>& dp, int LOG) {
	rep(i,0,LOG) rep(mask,0,1<<LOG) {
		if (mask & (1 << i)) {
			int bit_on = mask;
			int bit_off = mask ^ (1 << i);
			// dp[bit_on] += dp[bit_off];
		}
	}
}
