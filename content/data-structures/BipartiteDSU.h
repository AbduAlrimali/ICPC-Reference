/**
 * Author: Folklore
 * Date: 2024-05-20
 * License: CC0
 * Source: Standard competitive programming folklore
 * Description: Disjoint-set data structure with path compression and union by size. 
 * Maintains the parity of the path length from each node to its component's root. 
 * Can be used to check if a dynamically growing graph remains bipartite. 
 * The global \texttt{is\_bipartite} flag permanently becomes false if an odd cycle is added.
 * Time: $O(\alpha(N))$ amortized per operation.
 * Memory: $O(N)$
 * Status: Tested
 */
#pragma once

struct BipartiteDSU {
    vi e, parity;
    bool is_bipartite = true;
    BipartiteDSU(int n) : e(n, -1), parity(n, 0) {}
    int size(int x) { return -e[find(x)]; }
    int find(int x) { 
        if(e[x] < 0) return x;
        int root = find(e[x]);
        parity[x] ^= parity[e[x]];
        return e[x] = root;
    }
    void add_edge(int aa, int bb) {
        int a = find(aa), b = find(bb);
        if(a == b) {
            if(parity[aa] == parity[bb]){
                is_bipartite = false;
            }
        } else {
            if (e[a] > e[b]) swap(a, b);
            e[a] += e[b]; e[b] = a;
            parity[b] = parity[aa] ^ parity[bb] ^ 1;
        }
    }
};