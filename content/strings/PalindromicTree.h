/**
 * Author: AbduAlrimali
 * Date: 2026-07-21
 * Description: Palindromic Tree (Eertree). Stores all distinct palindromic substrings.
 * \texttt{cnt} contains the number of palindromic suffixes of the node.
 * \texttt{oc} tracks occurrences (call \texttt{calc\_occurrences} after building).
 * 
 * Time: $O(N)$ build, $O(N)$ for occurrence count.
 * Status: Tested
 */
#pragma once

struct PalindromicTree {
	struct Node {
		int nxt[26], len, st, en, link, cnt, oc;
	};

	string s;
	vector<Node> t;
	int sz, last;

	PalindromicTree(const string& _s = "") : s(_s) {
		int n = sz(s);
		t.assign(n + 3, {});
		sz = last = 2;
		t[1].len = -1; t[1].link = 1;
		t[2].len = 0;  t[2].link = 1;
		rep(i, 0, n) extend(i);
	}

	bool extend(int pos) {
		int cur = last, ch = s[pos] - 'a';
		while (pos - 1 - t[cur].len < 0 || s[pos - 1 - t[cur].len] != s[pos]) {
			cur = t[cur].link;
		}

		if (t[cur].nxt[ch]) {
			last = t[cur].nxt[ch];
			t[last].oc++;
			return false;
		}

		sz++; last = sz;
		t[sz].len = t[cur].len + 2;
		t[cur].nxt[ch] = sz;
		t[sz].en = pos;
		t[sz].st = pos - t[sz].len + 1;
		t[sz].oc = 1;

		if (t[sz].len == 1) {
			t[sz].link = 2;
			t[sz].cnt = 1;
			return true;
		}

		cur = t[cur].link;
		while (pos - 1 - t[cur].len < 0 || s[pos - 1 - t[cur].len] != s[pos]) {
			cur = t[cur].link;
		}

		t[sz].link = t[cur].nxt[ch];
		t[sz].cnt = 1 + t[t[sz].link].cnt;
		return true;
	}

	void calc_occurrences() {
		for (int i = sz; i >= 3; i--) {
			t[t[i].link].oc += t[i].oc;
		}
	}
};
