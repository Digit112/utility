#ifndef UTIL_VECTOR
#define UTIL_VECTOR

#include <math.h>
#include <stdio.h>

namespace util {
	template<class T> class vec2;
	template<class T> class vec3;
	template<class T> class vec4;
	
	template<class T> class complex;
	template<class T> class quaternion;

	template<class T> class vec2 {
	public:
		T x;
		T y;
		
		vec2();
		vec2(T x, T y);
		
		// Returns the magnitude of this vector
		double mag() const;
		// Returns the squared magnitude of this vector
		double sqr_mag() const;
		
		// Returns the argument of the vector.
		double arg();
		
		vec2<T> operator+(const vec2<T>& a) const;
		vec2<T> operator-(const vec2<T>& a) const;
		vec2<T> operator*(const vec2<T>& a) const;
		vec2<T> operator/(const vec2<T>& a) const;
		vec2<T> operator*(double a) const;
		vec2<T> operator/(double a) const;
		vec2<T> operator-() const;
		
		bool operator==(const vec2<T>& a) const;
		
		// Returns whether this vector is nan. Only returns true if all elements are nan.
		bool is_nan() const;
		
		// Returns a normalized version of this vector
		vec2<T> normalize();
		vec2<T> normalize(double t);
		
		// Returns the Dot Product of two vectors
		static double dot(const vec2<T>& a, const vec2<T>& b);	
	};
	
	template<class T> class vec3 {
	public:
		T x;
		T y;
		T z;
		
		vec3();
		vec3(double x, double y, double z);
		
		double mag() const;
		double sqr_mag() const;
		
		vec3<T> operator+(const vec3<T>& a) const;
		vec3<T> operator-(const vec3<T>& a) const;
		vec3<T> operator*(const vec3<T>& a) const;
		vec3<T> operator/(const vec3<T>& a) const;
		vec3<T> operator*(double a) const;
		vec3<T> operator/(double a) const;
		vec3<T> operator-() const;
		
		bool operator==(const vec3<T>& a);
		
		// Returns whether this vector is nan. Only returns true if all elements are nan.
		bool is_nan();
		
		vec3<T> normalize();
		vec3<T> normalize(double t);
		
		static double distance(const vec3<T>& a, const vec3<T>& b);
		
		static double dot(const vec3<T>& a, const vec3<T>& b);
		static vec3<T> cross(const vec3<T>& a, const vec3<T>& b);
		
		// Reflect the vector "a" across "b".
		// rev_reflect does the same, but also reverses the direction of the reflected vector.
		// Thus, rev_reflect returns the direction vector "a" is traveling after reflecting off of a surface with normal "b".
		static vec3<T> reflect(const vec3<T>& a, const vec3<T>& b);
		static vec3<T> rev_reflect(const vec3<T>& a, const vec3<T>& b);
	};
	
	template<class T> class vec4 {
	public:
		T w;
		T x;
		T y;
		T z;
		
		vec4<T>();
		vec4<T>(T w, T x, T y, T z);
		
		double mag() const;
		double sqr_mag() const;
		
		vec4<T> operator+(const vec4<T>& a) const;
		vec4<T> operator-(const vec4<T>& a) const;
		vec4<T> operator*(const vec4<T>& a) const;
		vec4<T> operator/(const vec4<T>& a) const;
		vec4<T> operator*(double a) const;
		vec4<T> operator/(double a) const;
		vec4<T> operator-() const;
		
		bool operator==(vec4<T> a);
		
		// Returns whether this vector is nan. Only returns true if all elements are nan
		bool is_nan();
		
		vec4<T> normalize();
		vec4<T> normalize(double t);
		
		static double dot(const vec4<T>& a, const vec4<T>& b);
	};
	
	template<class T> class complex : public vec2<T> {
	public:
		complex();
		complex(T r, T i);
		complex(double theta);
		
		complex(const vec2<T>&);
		
		complex<T> operator*(const complex<T>& a) const;
		complex<T> operator*(double a) const;
		
		static complex<T> scale(const complex<T>& a, const complex<T>& b);
		
		// Complex conjugation
		complex<T> operator~() const;
	};
	
	template<class T> class quaternion : public vec4<T> {
	public:
		quaternion();
		quaternion(T w, T x, T y, T z);
		quaternion(const vec3<T>& axis, double theta); // The constructor normalizes the axis for you.
		
		quaternion(const vec4<T>& a);
		
		quaternion operator=(const vec4<T>&) const;
		
		quaternion operator*(const quaternion& a) const; // Hamilton product
		quaternion operator*(double a) const;
		
		static quaternion scale(const quaternion& a, const quaternion& b);
		
		// Complex conjugation
		quaternion operator~() const;
		
		static quaternion hamilton(const quaternion& a, const quaternion& b);
		static vec3<T> vhamilton(const quaternion& a, const quaternion& b);
		
		quaternion& mhamilton(quaternion& a, const quaternion& b);
		
		// Normalize identical to the vecd4 normalize. This version exists so that quaternion::normalize() will return a quaternion.
		quaternion normalize();
		quaternion normalize(double t);
		
		// Rotates the passed vector according to the current quaternion about the origin.
		vec3<T> apply(const vec3<T>& in) const;
		
		// Rotate the given vector theta radians around the given axis or by applying the given quaternion.
		// Use offset to specify a point through which the axis of rotation passes.
		static vec3<T> rotate(const vec3<T>& in, const vec3<T>& axis_offset, const vec3<T>& axis_dir, double theta);
		static vec3<T> rotate(const vec3<T>& in, const vec3<T>& axis_offset, const quaternion<T>& r);
		
		// Interpolate between two quaternions in such a way as to produce smooth rotations.
		static quaternion<T> slerp(const quaternion<T>& a, const quaternion<T>& b, double t); 
	};

	template<class T> constexpr vec3<T> forward(1, 0, 0);
	template<class T> constexpr vec3<T> backward(-1, 0, 0);
	template<class T> constexpr vec3<T> right(0, 1, 0);
	template<class T> constexpr vec3<T> left(0, -1, 0);
	template<class T> constexpr vec3<T> up(0, 0, 1);
	template<class T> constexpr vec3<T> down(0, 0, -1);
	
	template<class T> constexpr complex<T> cid(1, 0);
	template<class T> constexpr quaternion<T> qid(1, 0, 0, 0);
}


#include "vec.cpp"

#endif
