/**
 * Author: Folklore
 * Date: 2026-06-28
 * License: CC0
 * Source: Standard competitive programming folklore
 * Description: Weighted Disjoint-set data structure with rollbacks. 
 * Maintains relative weights representing Value(u) - Value(v) = w.
 * Uses a state stack to support strictly O(1) rollbacks.
 * Uses Union-by-Size and NO path compression to preserve history.
 * If a cycle is formed, join() pushes a dummy state and returns whether the weight is consistent.
 * Time: O(\log N) per find/join, O(1) per rollback step.
 * Memory: O(N) for nodes, O(Q) for history stack.
 * Status: Tested
 */
#pragma once

struct RollbackWeightedDSU {
    vector<int> leader, sz;
    vector<long long> weight;
    int comps;

    // Struct to snapshot the exact state of the child node before it was merged
    struct State {
        int u; // The node that became a child (-1 if dummy)
        int v; // The node that became the parent
        int sz_v; // Old size of the parent
        long long weight_u; // Old weight of u (usually 0)
    };
    vector<State> st;

    RollbackWeightedDSU(int n) : leader(n + 1), sz(n + 1, 1), weight(n + 1, 0), comps(n) {
        // Initialize 1-based indexing (or 0-based, works for both)
        for(int i = 0; i <= n; i++) leader[i] = i;
    }

    // Returns {root, Value(x) - Value(root)}
    // Strictly O(log N) - NO path compression!
    pair<int, long long> find(int x) {
        if (x == leader[x]) return {x, 0};
        auto p = find(leader[x]);
        return {p.first, p.second + weight[x]}; // Accumulate distance to root
    }

    int time() { return st.size(); }

    void rollback(int t) {
        while (st.size() > t) {
            auto s = st.back();
            st.pop_back();
            
            if (s.u != -1) { // If an actual merge occurred
                leader[s.u] = s.u;      // Restore u to being its own root
                sz[s.v] = s.sz_v;       // Restore parent's size
                weight[s.u] = s.weight_u; // Restore u's weight
                comps++;                // A component split back into two
            }
        }
    }

    // Attempts to add the relationship Value(u) - Value(v) = w
    bool join(int u, int v, long long w) {
        auto pu = find(u), pv = find(v);
        int root_u = pu.first, root_v = pv.first;
        long long dist_u = pu.second, dist_v = pv.second;

        if (root_u == root_v) {
            // Push a dummy state to keep time() perfectly synchronized
            st.push_back({-1, -1, -1, 0});
            // Return true if the new edge is consistent, false if it contradicts
            return (dist_u - dist_v == w);
        }

        // Union by size to guarantee O(log N) height
        if (sz[root_u] > sz[root_v]) {
            swap(root_u, root_v);
            swap(dist_u, dist_v);
            w = -w; // CRITICAL: If we swap the merge direction, the relative distance flips!
        }

        // Snapshot the state before modifying
        st.push_back({root_u, root_v, sz[root_v], weight[root_u]});

        leader[root_u] = root_v;
        sz[root_v] += sz[root_u];
        // The derived triangle math formula
        weight[root_u] = w - dist_u + dist_v;
        comps--;

        return true;
    }
};