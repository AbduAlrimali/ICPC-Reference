/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * Description: For each position in a string, 
 * p[1][i] = (max  odd  length  palindrome  centered  at  i)  /  2  [floor  division], 
 * p[0][i] = same  for  even,  it  considers  the  right  center.
 * iterate over p[1][i] and p[0][i] to find the longest palindromic substring.
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

struct Manacher {
	vi p[2];
	Manacher(const string &s) {
		int n = sz(s);
		p[0].resize(n + 1);
		p[1].resize(n);
		rep(z, 0, 2) for(int i = 0, l = 0, r = 0; i < n; i++) {
				int t = r - i + !z;
				if(i < r)  p[z][i] = min(t, p[z][l + t]);
				int L = i - p[z][i], R = i + p[z][i] - !z;
				while(L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
					p[z][i]++, L--, R++;
				if (R > r) l = L, r = R;
			}
	}
	bool is_palindrome(int l,  int r) { // [l, r] inclusive
		int mid = (l + r + 1) / 2, len = r - l + 1;
		return 2 * p[len % 2][mid] + len % 2 >= len;
	}
};