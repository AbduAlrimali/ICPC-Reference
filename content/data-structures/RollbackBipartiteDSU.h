/**
 * Author: Folklore
 * Date: 2024-05-20
 * License: CC0
 * Source: Standard competitive programming folklore
 * Description: Bipartite Disjoint-set data structure with rollbacks. 
 * Maintains the parity of the path length to the root to check for odd-length cycles.
 * Uses a state stack to support strictly O(1) rollbacks to any previous time state.
 * Strictly uses Union-by-Size and NO path compression to preserve tree topology.
 * Time: O(\log N) per operation, O(1) per rollback step.
 * Memory: O(N) for nodes, O(Q) for history stack.
 * Status: Tested
 */
#pragma once

struct RollbackBipartiteUF {
    vi e, parity;
    int comps;
    int odd_cycles; // The graph is bipartite if odd_cycles == 0

    struct State {
        int u, e_u;
        int v, e_v, parity_v;
        int comps, odd_cycles;
    };
    vector<State> st;

    RollbackBipartiteUF(int n) : e(n, -1), parity(n, 0), comps(n), odd_cycles(0) {}
    int size(int x) { return -e[find(x).first]; }
    int time() { return sz(st); }
    bool is_bipartite() { return odd_cycles == 0; }

    // Returns {root, parity distance to root}
    // O(log n) because we CANNOT use path compression with rollbacks
    pii find(int x) {
        if (e[x] < 0) return {x, 0};
        pii p = find(e[x]);
        return {p.first, p.second ^ parity[x]};
    }

    void rollback(int t) {
        while (sz(st) > t) {
            auto s = st.back();
            st.pop_back();
            
            // If u != -1, an actual tree merge happened, so we restore the arrays
            if (s.u != -1) {
                e[s.u] = s.e_u;
                e[s.v] = s.e_v;
                parity[s.v] = s.parity_v;
            }
            
            // Always restore the global counters
            comps = s.comps;
            odd_cycles = s.odd_cycles;
        }
    }

    bool join(int x, int y) {
        pii px = find(x), py = find(y);
        int u = px.first, v = py.first;
        int parity_x = px.second, parity_y = py.second;

        if (u == v) {
            // Same component! Check if they have the same color.
            bool is_odd_cycle = (parity_x == parity_y);
            
            // Push a "dummy" state where u = -1 to keep track of time()
            st.push_back({-1, -1, -1, -1, -1, comps, odd_cycles});
            
            if (is_odd_cycle) odd_cycles++;
            return false;
        }
        if (e[u] > e[v]) {
            swap(u, v);
            swap(parity_x, parity_y);
        }
        st.push_back({u, e[u], v, e[v], parity[v], comps, odd_cycles});
        e[u] += e[v];
        e[v] = u;
        parity[v] = parity_x ^ parity_y ^ 1;
        comps--;
        return true;
    }
};