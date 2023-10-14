#include <stdio.h>

#include "util.hpp"

using namespace util;

int main() {
	// The point to be rotated.
	vecd3 p(1, 0, 1);
	
	// The axis to rotate around and amount to rotate in radians.
	vecd3 axis(2, 1, 1);
	float theta = 0.79; // About 45 degrees.
	
	//Create a quaternion to represent the rotation.
	quaternion rot(axis, theta);
	
	// Rotate the point.
	vecd3 p_n = rot.apply(p);
	
	// Prints (1.29, -0.14, 0.56)
	printf("(%.2f, %.2f, %.2f)\n", p_n.x, p_n.y, p_n.z);
	
	return 0;
}