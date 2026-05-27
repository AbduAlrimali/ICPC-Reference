/**
 * Author: common
 * Date: 2024-05-27
 * License: CC0
 * Description: Returns the incenter and inradius of a triangle.
 * Status: tested
 */
#pragma once
#include "Point.h"

template<class P>
pair<P, double> incenter(P a, P b, P c) {
	double la = (b - c).dist(), lb = (a - c).dist(), lc = (a - b).dist();
	P res = (a * la + b * lb + c * lc) / (la + lb + lc);
	double area = abs((b - a).cross(c - a)) / 2;
	return {res, 2 * area / (la + lb + lc)};
}
