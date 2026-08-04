/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * $\min(V[a], V[a + 1], \dots, V[b - 1])$ in constant time. 
 * Designed for half-open intervals $[a, b)$.
 * Usage:
 * RMQ rmq(values);
 * rmq.query(inclusive, exclusive); // [a, b)
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    vector<int> lg;
	RMQ(){}
    RMQ(const vector<T>& v) : jmp(1, v) {
        lg.assign(sz(v) + 1, 0);
        for(int i = 2;i<=sz(v);i++) lg[i] = lg[i / 2] + 1;
        for (int pw = 1, k = 1; pw * 2 <= sz(v); pw *= 2, ++k) {
            jmp.emplace_back(sz(v) - pw * 2 + 1);
            rep(j,0,sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) { // query on [a, b)
        if(a==b) return T();
        if(a>b) swap(a, b);
        int dep = lg[b-a];
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
