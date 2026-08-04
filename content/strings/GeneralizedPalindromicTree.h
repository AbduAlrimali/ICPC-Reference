/**
 * Author: AbduAlrimali
 * Date: 2026-07-22
 * Description: Generalized Palindromic Tree (Eertree) for multiple strings.
 * \texttt{in\_how\_many} counts how many distinct strings contain each palindromic substring.
 * A string of length $L$ can add a maximum of $L$ new nodes to the Palindromic Tree.
 * Time: $O(L)$ to add a string of length $L$.
 * Status: Tested
 */
#pragma once

struct GeneralizedPalindromicTree {
	struct Node {
		int nxt[26], len, st, en, link, cnt, oc;
	};

	string s;
	vector<Node> t;
	int sz, last;
	vector<int> last_seen, in_how_many;

	// Allocate memory exactly for the sum of lengths in the current test case
	GeneralizedPalindromicTree(int max_len) {
		t.assign(max_len + 3, {});
		last_seen.assign(max_len + 3, 0);
		in_how_many.assign(max_len + 3, 0);
		sz = last = 2;
		t[1].len = -1; t[1].link = 1;
		t[2].len = 0;  t[2].link = 1;
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

	void add_string(const string& _s, int string_id) {
		s = _s;
		last = 2; // Crucial: Reset to root for the new string
		vector<int> nodes;

		for (int i = 0; i < sz(s); i++) {
			extend(i);
			nodes.push_back(last);
		}

		// Push string presence up the suffix links
		for (int u : nodes) {
			int curr = u;
			// Stop early if this node was already seen in the current string
			while (curr > 2 && last_seen[curr] != string_id) {
				last_seen[curr] = string_id;
				in_how_many[curr]++;
				curr = t[curr].link;
			}
		}
	}
};
