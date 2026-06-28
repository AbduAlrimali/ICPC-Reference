/**
 * Author: Unknown
 * Date: 2026-05-28
 * License: CC0
 * Description: Returns the shortest distance between two line segments.
 * Time: O(1)
 * Status: Tested
 */
#pragma once

#include "SegmentDistance.h"
#include "SegmentIntersection.h"

double segSegDist(P a, P b, P c, P d) {
	if (!segInter(a, b, c, d).empty()) return 0;
	return min({segDist(a, b, c), segDist(a, b, d),
	            segDist(c, d, a), segDist(c, d, b)});
}
