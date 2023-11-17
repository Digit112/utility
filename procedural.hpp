#ifndef UTIL_PROCEDURAL
#define UTIL_PROCEDURAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <cstdint>

namespace util {
	class pattern2;
	class procedural;
	
	/// Generate random values using xoshiro** 1.1
	/** I recommend this rng for general-purpose image generation.
	*   Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)
	*   Original <http://xoshiro.di.unimi.it/xoshiro128starstar.c> */
	class rng_xoshiro_starstar {
	public:
		/// The state of the random number generator.
		uint32_t seed[4];
		
		// RNG initialization
		void init(uint32_t sd = 0);
		
		// RNG functions
		int random_int();
		float random_val();
	};
	
	/// Implements hash functions.
	class hashing {
	public:
		static uint32_t FNV_32(uint32_t seed);
		static uint32_t FNV_32(uint64_t seed);
		static uint32_t FNV_32(const char* seed);
	};
	
	// simple class for holding 2D monochrome data.
	class pattern2 {
	public:
		int width;
		int height;
		
		float* data;
		
		pattern2();
		pattern2(const pattern2&);
		pattern2(int width, int height);
		pattern2(int width, int height, float fill);
		
		// Assignment opertor deep copies.
		void operator=(const pattern2&);
		
		void saveppm(const char* fn);
		
		void fill(float val);
		
		// Add all values in the pattern by a number.
		void add(float val);
		
		// Multiply all values in the pattern by a number.
		void scale(float val);
		
		// Copy the supplied pattern over this pattern, aligning the upper left corner to x and y and with the given opacity ranging from 0 to 1.
		void paint(pattern2 p, float opacity = 1, int x = 0, int y = 0);
		
		// Same as paint(), but add the values instead of averaging them.
		void add(pattern2 p, int x = 0, int y = 0);
		
		// Same as paint() but multiply values instead of averaging them.
		void scale(pattern2 p, int x = 0, int y = 0);
		
		// Scale all the values in this pattern such that the lowest becomes 0 and the highest becomes 1
		void fit_values();
		
		// Set all values below min to min, and all values above max to max.
		void clamp(float min = 0, float max = 1);
		
		// Set each value in this pattern to the max or min between itself and another pattern.
		void max(pattern2 p);
		void min(pattern2 p);
		
		~pattern2();
	};
	
	class procedural {
	public:
		// RNG
		rng_xoshiro_starstar rng;
		
		// Preset vector choices for simplex noise generation
		const vec2<float> vecpick2[4] = {vec2<float>(1, 1), vec2<float>(1, -1), vec2<float>(-1, 1), vec2<float>(-1, -1)};
		//const vecd3 vecpick3[12];
		
		procedural();
		
		/* Simple patterns. All coordinates and distances are given in pixels. */
		
		// Generate a sine wave emanating from a point.
		pattern2& sin_circle(pattern2& p, int x, int y, int wavelength, float offset = 0);
		
		// Generate a circle around a point where the brightness of each pixel falls off with the common log
		pattern2& log_circle(pattern2& p, int x, int y, int r);
		
		// Same as log_circle, but using the natural log.
		pattern2& ln_circle(pattern2& p, int x, int y, int r);
		
		// Generates a circle where brightness falls off with linear distance from the circle's center.
		pattern2& lin_circle(pattern2& p, int x, int y, int r);
		
		// Creates a circle where brightness falls off according to a logistic curve.
		// This circle technically  continues forever, and will be at 0.5 brightness at radius r.
		// "s" controls the steepness of the falloff, S=0 will have no falloff and will paint everything 0.5. Negative steepness inverts the circle!
		pattern2& logistic_circle(pattern2& p, int x, int y, int r, float s);
		
		// Generate a sine wave with the given wavelength and offset propagating in the direction (dx, dy)
		pattern2& sin_wave(pattern2& p, float dx, float dy, int wavelength, float offset=0);
		
		// Generate a gradient between the two given values.
		pattern2& lin_gradient(pattern2& p, float dx, float dy, float start=0, float end=1);
		
		/* Random Noise */
		
		// 2D Simplex Noise
		pattern2& simplex(pattern2& p, float maxX, float maxY, float minX = 0, float minY = 0);
		
		// 2D Worley Noise
		pattern2& worley(pattern2& p, float maxX, float maxY, float minX = 0, float minY = 0);
		
		/* Operations */ 
		
		// Rounds the values of all pixels towards the nearest multiple of "inc".
		pattern2& band(pattern2& p, float inc);
	};
}

#include "procedural.cpp"

#endif
