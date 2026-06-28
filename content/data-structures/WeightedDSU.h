/**
 * Author: Folklore
 * Date: 2026-06-28
 * License: CC0
 * Source: Standard competitive programming folklore
 * Description: Disjoint-set data structure with path compression. 
 * Maintains relative weights/distances between nodes in the same component.
 * \texttt{Union(u, v, w)} adds a directed relationship representing $Value(u) - Value(v) = w$.
 * Returns false if the new relationship contradicts existing paths (cycle detection).
 * Time: $O(\alpha(N))$ amortized per operation.
 * Memory: $O(N)$
 * Status: Tested
 */
#pragma once

struct WeightedDSU {  
    vi leader, sz;
    vector<ll> weight;
    
    WeightedDSU(int n) : leader(n+1, -1), sz(n+1, 1), weight(n+1) { }  
    int find(int u) {  
        if(leader[u]<0) return u;  
        int root = find(leader[u]); // Recursion first!
        weight[u] += weight[leader[u]];
        return leader[u] = root;  
    }  
  
    bool Union(int u, int v, long long w) {  
        int root_u = find(u); 
        int root_v = find(v);
        if(root_u != root_v) {
            leader[root_u] = root_v;  
            sz[root_v] += sz[root_u]; 
            weight[root_u] = w - weight[u] + weight[v]; // Apply the derived formula
            return true;
        } else {
            // Check consistency: (u - root) - (v - root) == w 
            return (weight[u] - weight[v] == w);
        }
    }  
};