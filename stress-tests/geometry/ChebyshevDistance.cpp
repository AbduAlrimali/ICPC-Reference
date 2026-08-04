#include "../utilities/template.h"
#include "../../content/geometry/ChebyshevDistance.h"

void test_chebyshev() {
    Point<ll> p1(2, 3);
    Point<ll> p2(5, 7);

    // Manhattan distance in original space
    ll original_manhattan = abs(p1.x - p2.x) + abs(p1.y - p2.y);
    assert(original_manhattan == 7);

    // Chebyshev distance in original space
    ll original_chebyshev = max(abs(p1.x - p2.x), abs(p1.y - p2.y));
    assert(original_chebyshev == 4);

    // Transform points to Chebyshev space
    Point<ll> c1 = toChebyshev(p1);
    Point<ll> c2 = toChebyshev(p2);

    // Chebyshev distance in rotated space equals Manhattan distance in original space
    ll rotated_chebyshev = max(abs(c1.x - c2.x), abs(c1.y - c2.y));
    assert(rotated_chebyshev == original_manhattan);

    // Manhattan distance in rotated space is 2 * Chebyshev distance in original space
    ll rotated_manhattan = abs(c1.x - c2.x) + abs(c1.y - c2.y);
    assert(rotated_manhattan == 2 * original_chebyshev);

    // Convert back from Chebyshev space to Manhattan space
    Point<double> m1 = toManhattan(c1);
    Point<double> m2 = toManhattan(c2);
    assert(abs(m1.x - p1.x) < 1e-9);
    assert(abs(m1.y - p1.y) < 1e-9);
    assert(abs(m2.x - p2.x) < 1e-9);
    assert(abs(m2.y - p2.y) < 1e-9);
}

int main() {
    test_chebyshev();
    cout << "ChebyshevDistance tests passed!" << endl;
    return 0;
}
