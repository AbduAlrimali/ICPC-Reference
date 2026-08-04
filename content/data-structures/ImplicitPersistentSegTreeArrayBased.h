/**
 * Author: Unknown
 * Date: 2026-07-25
 * License: CC0
 * Source: Unknown
 * Description: Array-based Implicit Persistent Segment Tree. Operates on a dynamic value range
 * without coordinate compression.
 * Time: O(\log(\text{domain\textunderscore size})) per query/update.
 * Memory: O(N \log(\text{domain\textunderscore size}))
 * Status: unverified
 */
#pragma once

const int N = 2e5 + 5;
const int MAX_NODES = N * (__lg(1000000001) + 2); // N * (__lg(domain_size) + 2)
int lc_arr[MAX_NODES];
int rc_arr[MAX_NODES];
ll val_arr[MAX_NODES];
int roots[N]; // Assuming n <= 200000
int node_cnt = 0;

int update(int node, ll L, ll R, ll pos, ll val) {
	int cur = ++node_cnt;
	lc_arr[cur] = lc_arr[node];
	rc_arr[cur] = rc_arr[node];
	val_arr[cur] = val_arr[node] + val;

	if (L == R) return cur;

	ll mid = L + (R - L) / 2;
	if (pos <= mid) {
		lc_arr[cur] = update(lc_arr[node], L, mid, pos, val);
	} else {
		rc_arr[cur] = update(rc_arr[node], mid + 1, R, pos, val);
	}
	return cur;
}

ll query(int node, ll L, ll R, ll ql, ll qr) {
	if (!node || L > qr || R < ql) return 0;
	if (ql <= L && R <= qr) return val_arr[node];

	ll mid = L + (R - L) / 2;
	return query(lc_arr[node], L, mid, ql, qr) +
	       query(rc_arr[node], mid + 1, R, ql, qr);
}
