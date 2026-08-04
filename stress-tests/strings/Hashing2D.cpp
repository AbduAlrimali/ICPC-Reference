#include "../utilities/template.h"
#include "../../content/strings/Hashing2D.h"

void test_hashing2d() {
    int R = 4, C = 4;
    vector<string> grid = {
        "abcd",
        "efgh",
        "abcd",
        "efgh"
    };

    ll BR = 131, BC = 137, MOD = 1e9 + 7;
    RollingHash2D rh(R, C, BR, BC, MOD);
    rh.build(grid);

    // Identical subgrids (0,0)-(1,3) and (2,0)-(3,3)
    assert(rh.get(0, 0, 1, 3) == rh.get(2, 0, 3, 3));

    // Identical 1x1 subgrids 'a'
    assert(rh.get(0, 0, 0, 0) == rh.get(2, 0, 2, 0));

    // Identical 2x2 subgrids
    // "ab"
    // "ef"
    assert(rh.get(0, 0, 1, 1) == rh.get(2, 0, 3, 1));

    // Non-identical subgrids
    assert(rh.get(0, 0, 0, 1) != rh.get(0, 1, 0, 2)); // "ab" != "bc"
}

int main() {
    test_hashing2d();
    cout << "Hashing2D tests passed!" << endl;
    return 0;
}
