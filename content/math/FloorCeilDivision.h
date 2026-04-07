/**
 * Author: User
 * Date: 2026-04-07
 * Description: Mathematical floor and ceiling division. Standard C++ integer 
 * division truncates towards zero, which is incorrect for negative numbers. 
 * These functions correctly compute $\lfloor a / b \rfloor$ and $\lceil a / b \rceil$ 
 * for all signed integers using bitwise sign checking.
 * Time: $O(1)$
 */
#pragma once

ll floor_div(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b != 0);
}

ll ceil_div(ll a, ll b) {
    return a / b + ((a ^ b) > 0 && a % b != 0);
}