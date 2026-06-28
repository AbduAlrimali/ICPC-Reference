/**
 * Author: Folklore
 * Date: 2026-06-28
 * License: CC0
 * Source: Standard competitive programming folklore
 * Description: array-based persistent segment tree used to track previous changes and rollback to a certain point in time.
 * Status: Tested
 */

struct pSeg {
    struct Node {
        ll sum;
        int l, r;
    };
    
    vector<Node> tree;
    vector<int> root;
    int sz;

    pSeg(vector<ll>& arr) : sz(arr.size()) {
        tree.reserve(6000000); // Pre-allocate to prevent reallocation MLE
        tree.push_back({0, 0, 0}); // Dummy node at index 0
        root.push_back(build(0, sz - 1, arr));
    }

    int new_node(ll sum, int l = 0, int r = 0) {
        tree.push_back({sum, l, r});
        return tree.size() - 1;
    }

    int build(int l, int r, vector<ll>& a) {
        if (l == r) return new_node(a[l]);
        int m = (l + r) / 2;
        int left_child = build(l, m, a);
        int right_child = build(m + 1, r, a);
        return new_node(tree[left_child].sum ^ tree[right_child].sum, left_child, right_child);
    }

    int set(int v, int l, int r, int pos, ll val) {
        if (l == r) return new_node(val);
        int m = (l + r) / 2;
        if (pos <= m) {
            int left_child = set(tree[v].l, l, m, pos, val);
            return new_node(tree[left_child].sum ^ tree[tree[v].r].sum, left_child, tree[v].r);
        } else {
            int right_child = set(tree[v].r, m + 1, r, pos, val);
            return new_node(tree[tree[v].l].sum ^ tree[right_child].sum, tree[v].l, right_child);
        }
    }

    void copy(int idx) {
        root.push_back(root[idx]); 
    }

    void set(int idx, int pos, ll val) {
        root[idx] = set(root[idx], 0, sz - 1, pos, val);
    }

    ll query(int node_l, int node_r, int l, int r) {
        ll res = tree[node_l].sum ^ tree[node_r].sum;
        if (res == 0) return -1;
        if (l == r) return l;
        
        int m = (l + r) / 2;
        ll left_res = tree[tree[node_l].l].sum ^ tree[tree[node_r].l].sum;
        
        if (left_res > 0) {
            return query(tree[node_l].l, tree[node_r].l, l, m);
        } else {
            return query(tree[node_l].r, tree[node_r].r, m + 1, r);
        }
    }

    ll query(ll l, ll r) {
        return query(root[l - 1], root[r], 0, sz - 1);
    }
};