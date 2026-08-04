/**
 * Author: Unknown
 * Date: 2026-07-17
 * License: CC0
 * Source: custom
 * Description: Dynamic/sparse segment tree using an array/vector-based representation.
 * Supports range set updates and range sum queries.
 * Time: $O(\log N)$ per update/query.
 * Usage: SparseSegmentTree<> tree(N);
 * Status: tested
 */
#pragma once

struct Node { 
    ll val = 0, lazy = 0; 
    bool is_lazy = false; 
    int left = -1, right = -1; 

    void apply(ll x, int l, int r) { 
        val = x*(r-l+1); 
        lazy = x; 
        is_lazy = true; 
    } 
}; 

template<typename T = ll> 
struct SparseSegmentTree {  
#define L tree[node].left 
#define R tree[node].right
#define MID ((l+r)>>1)  
private:  
    int sz, timer=0;  
    vector<Node> tree;
    T identity;


    inline void grow(int &node) {
        if (L == -1) { L = ++timer; tree.push_back(Node()); }
        if (R == -1) { R = ++timer; tree.push_back(Node()); }
    }
    
    void propagate(int node, int l, int r){
        if(!tree[node].is_lazy || l == r) return;
        tree[L].apply(tree[node].lazy, l, MID);
        tree[R].apply(tree[node].lazy, MID+1, r);
        tree[node].is_lazy = false; tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int ql, int qr, T val) {
        if (l > qr || r < ql) return;
        if (ql <= l && r <= qr) {
            tree[node].apply(val, l, r);
            return;
        }
        grow(node);
        propagate(node, l, r);
        update(L, l, MID, ql, qr, val);
        update(R, MID + 1, r, ql, qr, val);
        tree[node].val = tree[L].val + tree[R].val;
    }
    T query(int node, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return identity;
        if (ql <= l && r <= qr) return tree[node].val;
        grow(node);
        propagate(node, l, r);
        ll res = 0;
        res += query(L, l, MID, ql, qr);
        res += query(R, MID + 1, r, ql, qr);
        return res;
    }
public:  
    SparseSegmentTree(int n, int q=0) : sz(n) {
        if (q > 0) { tree.reserve(100 * q); }
        tree.push_back(Node()); // root node
        identity=0;
    }
    void update(int lq, int rq, T val) { update(0, 0, sz-1, lq, rq, val);  }  
    T query(int lq, int rq) { return query(0, 0, sz-1, lq, rq); }  
#undef L  
#undef R  
#undef MID  
};
