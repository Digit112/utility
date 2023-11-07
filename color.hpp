#ifndef UTIL_COLOR
#define UTIL_COLOR

namespace util {
	class rgb;
	class hsv;

	class rgb {
	public:
		float r;       // a fraction between 0 and 1
		float g;       // a fraction between 0 and 1
		float b;       // a fraction between 0 and 1
		
		rgb() : r(0), g(0), b(0) {}
		rgb(float r, float g, float b) : r(r), g(g), b(b) {}
		rgb(hsv in);
	};

	class hsv {
	public:
		float h;       // angle in degrees
		float s;       // a fraction between 0 and 1
		float v;       // a fraction between 0 and 1
		
		hsv() : h(0), s(0), v(0) {}
		hsv(float h, float s, float v) : h(h), s(s), v(v) {}
		hsv(rgb in);
	};
}

#include "color.cpp"

#endif