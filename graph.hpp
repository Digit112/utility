#ifndef UTIL_GRAPH
#define UTIL_GRAPH

namespace util {
	class linear;
	class quadratic;
	class cubic;
	
	// A linear polynomial
	class linear {
	public:
		// ax + b;
		float a;
		float b;
		
		linear() : a(0), b(0) {}
		
		linear(float a, float b) : a(a), b(b) {}
		
		linear(float b) : a(0), b(b) {}
		
		// Get the derivative.
		float derivative() const;
		
		// Get the integral. C becomes the constant term.
		quadratic integrate(float C) const;
		
		// Evaluate at some value x.
		float evaluate(float x) const;
	};
	
	// A quadratic polynomial
	class quadratic {
	public:
		// ax^2 + bx + c
		float a;
		float b;
		float c;
		
		quadratic() : a(0), b(0), c(0) {}
		
		quadratic(float a, float b, float c) : a(a), b(b), c(c) {}
		
		quadratic(const linear& bc) : a(0), b(bc.a), c(bc.b) {}
		quadratic(float c) : a(0), b(0), c(c) {}
		
		// Get the derivative.
		linear derivative() const;
		
		// Get the integral. C becomes the constant term.
		cubic integrate(float C) const;
		
		// Evaluate at some value x.
		float evaluate(float x) const;
	};
	
	// A cubic polynomial.
	class cubic {
	public:
		// ax^3 + bx^2 + cx + d
		float a;
		float b;
		float c;
		float d;
		
		cubic() : a(0), b(0), c(0), d(0) {}
		
		cubic(float a, float b, float c, float d) : a(a), b(b), c(c), d(d) {}
		
		cubic(const quadratic& bcd) : a(0), b(bcd.a), c(bcd.b), d(bcd.c) {}
		cubic(const linear& cd) : a(0), b(0), c(cd.a), d(cd.b) {}
		cubic(float d) : a(0), b(0), c(0), d(d) {}
		
		// Get the derivative.
		quadratic derivative() const;
		
		// Evaluate at some value x.
		float evaluate(float x) const;
	};
	
	// A class for performing cubic interpolation.
	// Provide the points to interpolate() and grab the resulting polynomials from cubic_interpolate.segments
	// The number of segments is one less than the number of points passed to the function.
	// The interpolate() has O(n^2) memory usage.
	class cubic_interpolator {
	public:
		int num_segments;
		cubic* segments;
		
		cubic_interpolator() : num_segments(0), segments(nullptr) {}
		
		bool interpolate(int num_points, vec2<float>* points);
		
		~cubic_interpolator();
	};
}

#include "graph.cpp"

#endif