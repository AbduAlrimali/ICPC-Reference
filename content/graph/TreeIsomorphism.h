/**
 * Author: Custom
 * Date: 2026-07-19
 * License: CC0
 * Description: Rooted unordered tree isomorphism using the Aho-Hopcroft-Ullman (AHU) 
 * algorithm. Computes a canonical integer ID for a specific rooted structure. 
 * The ID map is kept global for memoization across multiple test cases.
 * Time: $O(N \log N)$ per test case.
 * Status: Tested
 */
#pragma once

struct RootedTreeIso {
    map<vi, int> canonical_id;
    vi data;
    int id=0;

    int get_id(vi& children) {
        sort(children.begin(), children.end()); // remove sorting if ordered
        auto [it, inserted] = canonical_id.try_emplace(children, id);
        if (inserted) id++;
        return it->second;
    }

    int get_rooted_id(int u, int p, const vector<vi>& adj) {
        vi c;
        for (int v : adj[u]) {
            if (v != p) c.push_back(get_rooted_id(v, u, adj));
        }
        return data[u]=get_id(c);
    }

    vi compute(int root, const vector<vi>& adj) {
        data.assign(sz(adj), -1);
        get_rooted_id(root, -1, adj);
        return data;
    }
} tree_iso;
