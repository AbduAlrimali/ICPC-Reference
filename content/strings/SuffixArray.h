/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index (0-based) of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * \texttt{rank[i]} is the rank (1-based) of the ith suffix (0-based) in the initial string.
 * \texttt{rank[i]} is of size $n+1$, and \texttt{rank[n] = 0}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any nul chars.
 * In sa[i] and lcp[i], the index i is relative to sorted suffixes.
 * sa[i] and lcp[i] ask: "Tell me about the suffix that ended up at position i after sorting."
 * In rank[i], the index i is relative to the initial string.
 * rank[i] asks: "Where did the suffix starting at index i in the original string end up after sorting?"
 * Time: $O(n \log n)$
 * Status: stress-tested
 */
#pragma once

#include "RMQ.h"

struct SuffixArray {
	vi sa, lcp, rank;
    // RMQ<int> table;
    int n;
	SuffixArray(string s, int lim=256) { // or vector<int>
		s.push_back(0); n = sz(s); int k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
        rank = x;
        // table = RMQ(lcp);
	}
    // int get_lcp(int i, int j) { // lcp of ith and jth suffixes in the original string
    //     if (i == j) return n - 1 - i; 
    //     int u = rank[i], v = rank[j];
    //     if (u > v) swap(u, v);
    //     return table.query(u + 1, v + 1); 
    // }
};
