/**
 * Author: User
 * Date: 2025-01-15
 * License: CC0
 * Source: Standard
 * Description: Centroid Decomposition generic template. 
 * Currently configured to count paths of length $K$.
 * Run `decomp()` once. For queries and updates, implement `update()` and `query()`.
 * Can be modified to store $\log N$ ancestors/hubs per node.
 * Time: $O(N \log N)$
 */

#pragma once

ll k, ans=0;
const int N = 2e5+5;
int sz[N], rem[N], cnt[N];
int cent_par[N]; // Stores the parent of each node in the Centroid Tree
vector<int> adj[N];

int get_sz(int u, int p){ // get size of subtree of u
    sz[u]=1;
    for(int v:adj[u]){
        if (v != p && !rem[v]) sz[u] += get_sz(v, u);
    }
    return sz[u];
}
int get_centroid(int u, int p, int tot){ // get centroid of the subtree of u
    for(int v:adj[u]){
        if (v != p && !rem[v] && sz[v] > tot / 2) return get_centroid(v, u, tot);
    }
    return u;
}
void dfs_add(int u, int p, int dep, int delta){
    cnt[dep] += delta;
    for(int v:adj[u]){
        if(v==p || rem[v]) continue;
        dfs_add(v, u, dep+1, delta);
    }
}
void get_ans(int u, int p, int dep){
    if(dep<=k) ans += cnt[k-dep];
    for(int v:adj[u]){
        if(v==p || rem[v])continue;
        get_ans(v, u, dep+1);
    }
}
void decomp(int u, int p = -1){
    int comp_sz = get_sz(u, -1);
    int cent = get_centroid(u, -1, comp_sz);
    // get ans through current centroid
    cnt[0]=1;
    for(int v:adj[cent]){
        if(rem[v]) continue;
        get_ans(v, cent, 1);
        dfs_add(v, cent, 1, 1);
    }
    memset(cnt, 0, comp_sz*sizeof(int));
    // Save the centroid tree structure
    cent_par[cent] = p;
    // remove centroid and decompose
    rem[cent]=1;
    for(int v:adj[cent]){
        if(rem[v]) continue;
        decomp(v, cent);
    }
}