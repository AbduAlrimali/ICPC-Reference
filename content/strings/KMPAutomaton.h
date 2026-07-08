/**
 * Author: 
 * Date: 2026-07-07
 * License: CC0
 * Source: Standard NFA-to-DFA String DP
 * Description: Builds a deterministic finite automaton (DFA) for KMP string matching.
 * next[i][c] returns the next state after appending character c (0-indexed offset from 'a')
 * to a matched prefix of length i. If absorbing is true, the automaton stays in state m 
 * indefinitely once a full match is found (useful for "contains" queries).
 * Here $\Sigma = 26$.
 * Time: O(m \Sigma)
 * Status: tested
 */
#pragma once

vector<vi> buildAutomaton(int m, const vi& LPS, const string& P, bool absorbing = false) {
    vector<vi> nxt(m + 1, vi(26));
    for (int matched = 0; matched <= m; matched++) {
        for (int ch = 0; ch < 26; ch++) {
            if (absorbing && matched == m) {
                nxt[matched][ch] = m;
                continue;
            }
            int nj = matched;
            if (nj == m) nj = LPS[m - 1];
            while (nj > 0 && P[nj] - 'a' != ch) nj = LPS[nj - 1];
            if (P[nj] - 'a' == ch) nj++;
            nxt[matched][ch] = nj;
        }
    }
    return nxt;
}