#include "../utilities/template.h"
#include "../../content/data-structures/RMQ.h"
#include "../../content/graph/LCAForest.h"

void test_forest() {
    int n = 10;
    vector<vi> adj(n);
    // Tree 1: 0-1, 1-2, 1-3
    adj[0].push_back(1); adj[1].push_back(0);
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);

    // Tree 2: 4-5, 5-6 (rooted at 4: 4 -> 5 -> 6)
    adj[4].push_back(5); adj[5].push_back(4);
    adj[5].push_back(6); adj[6].push_back(5);

    // Isolated: 7, 8, 9

    LCAForest lca(adj);

    // Check tree 1 LCAs
    assert(lca.lca(2, 3) == 1);
    assert(lca.lca(0, 2) == 0);
    assert(lca.lca(2, 2) == 2);
    assert(lca.dist(2, 3) == 2);
    assert(lca.dist(0, 3) == 2);

    // Check tree 2 LCAs
    assert(lca.lca(4, 6) == 4);
    assert(lca.lca(5, 6) == 5);
    assert(lca.dist(4, 6) == 2);
    assert(lca.dist(5, 6) == 1);

    // Check isolated node
    assert(lca.lca(7, 7) == 7);
    assert(lca.dist(7, 7) == 0);
}

int main() {
    test_forest();
    cout << "LCAForest stress test passed!" << endl;
    return 0;
}
