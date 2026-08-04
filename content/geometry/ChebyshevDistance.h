/**
 * Author: 
 * Date: 2026-07-21
 * License: CC0
 * Source: Folklore
 * Description: Coordinate transformation to convert between Manhattan and Chebyshev distances.
 * Manhattan distance $|x_1 - x_2| + |y_1 - y_2|$ in the original space
 * becomes Chebyshev distance $\max(|u_1 - u_2|, |v_1 - v_2|)$ in the rotated/scaled space where $(u, v) = (x + y, x - y)$.
 * Chebyshev distance $\max(|x_1 - x_2|, |y_1 - y_2|)$ in the original space
 * becomes half of Manhattan distance $\frac{1}{2}(|u_1 - u_2| + |v_1 - v_2|)$ in the rotated/scaled space where $(u, v) = (x + y, x - y)$.
 * Useful for mapping tilted search regions (Manhattan) to axis-aligned squares (Chebyshev/2D Range Queries).
 * Time: O(1)
 */
#pragma once

#include "Point.h"

template<class T>
Point<T> toChebyshev(Point<T> p) {
	return Point<T>(p.x + p.y, p.x - p.y);
}

template<class T>
Point<double> toManhattan(Point<T> p) {
	return Point<double>((p.x + p.y) / 2.0, (p.x - p.y) / 2.0);
}
