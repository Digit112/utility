#ifndef UTIL_GEOMETRY
#define UTIL_GEOMETRY

#include "vec.hpp"

namespace util {
	// Rearranges the passed three points so that the longest side of the triangle formed by the points is side AB.
	// It accomplishes this by swapping a pair of points if necessary.
	void format_tri(vecd3& a, vecd3& b, vecd3& c);
	
	// Returns the point at which the passed ray passing through point P in direction D collides with triangle A, B, C,
	// or returns (nan, nan, nan) if no collision exists. D must be normalized already.
	// This function assumes that the points are not collinear, that d is normalized, and that AB is the longest line of the triangle.
	vecd3 coll_ray_tri(vecd3 p, vecd3 d, vecd3 a, vecd3 b, vecd3 c);
}

#include "geometry.cpp"

#endif
