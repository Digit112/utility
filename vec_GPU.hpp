#ifndef UTIL_VECTOR
#define UTIL_VECTOR

#include <math.h>
#include <stdio.h>

#define UTIL_GPU_QUAL __host__ __device__

namespace util {
	template<class T> class vec2;
	template<class T> class vec3;
	template<class T> class vec4;
	
	template<class T> class complex;
	template<class T> class quaternion;
	
	// IMPORTANT: Operations between vec2 objects with different template parameters
	// may return unexpected results. The right operand and return result will be converted
	// to the type of the left operand.
	template<class T> class vec2 {
	public:
		T x;
		T y;
		
		vec2();
		vec2(T x, T y);
		
		// Vectors are always implicitly convertable to all integer and floating-point types.
		UTIL_GPU_QUAL vec2(const vec2<signed char>& o);
		UTIL_GPU_QUAL vec2(const vec2<signed short>& o);
		UTIL_GPU_QUAL vec2(const vec2<signed int>& o);
		UTIL_GPU_QUAL vec2(const vec2<signed long int>& o);
		UTIL_GPU_QUAL vec2(const vec2<signed long long int>& o);
		
		UTIL_GPU_QUAL vec2(const vec2<unsigned char>& o);
		UTIL_GPU_QUAL vec2(const vec2<unsigned short>& o);
		UTIL_GPU_QUAL vec2(const vec2<unsigned int>& o);
		UTIL_GPU_QUAL vec2(const vec2<unsigned long int>& o);
		UTIL_GPU_QUAL vec2(const vec2<unsigned long long int>& o);
		
		UTIL_GPU_QUAL vec2(const vec2<float>& o);
		UTIL_GPU_QUAL vec2(const vec2<double>& o);
		UTIL_GPU_QUAL vec2(const vec2<long double>& o);
		
		// Returns the magnitude of this vector
		UTIL_GPU_QUAL double mag() const;
		// Returns the squared magnitude of this vector
		UTIL_GPU_QUAL double sqr_mag() const;
		
		// Returns the argument of the vector.
		// I.e. the angle counter-clockwise from the positive x-axis to this vector.
		UTIL_GPU_QUAL double arg();
		
		UTIL_GPU_QUAL vec2<T> operator+(const vec2<T>& a) const;
		UTIL_GPU_QUAL vec2<T> operator-(const vec2<T>& a) const;
		UTIL_GPU_QUAL vec2<T> operator*(const vec2<T>& a) const;
		UTIL_GPU_QUAL vec2<T> operator/(const vec2<T>& a) const;
		UTIL_GPU_QUAL vec2<T> operator*(double a) const;
		UTIL_GPU_QUAL vec2<T> operator/(double a) const;
		UTIL_GPU_QUAL vec2<T> operator-() const;
		
		UTIL_GPU_QUAL bool operator==(const vec2<T>& a) const;
		
		// Returns whether this vector is nan. Only returns true if all elements are nan.
		UTIL_GPU_QUAL bool is_nan() const;
		
		// Returns a normalized version of this vector
		UTIL_GPU_QUAL vec2<T> normalize();
		UTIL_GPU_QUAL vec2<T> normalize(double t);
		
		UTIL_GPU_QUAL static double distance(const vec2<T>& a, const vec2<T>& b);
		UTIL_GPU_QUAL static double sqr_distance(const vec2<T>& a, const vec2<T>& b);
		
		// Returns the Dot Product of two vectors
		UTIL_GPU_QUAL static double dot(const vec2<T>& a, const vec2<T>& b);
		
		// Reflect the vector a across n.
		// rev_reflect does the same, but also reverses the direction of the reflected vector.
		// Thus, rev_reflect returns the direction vector a is traveling after reflecting off of a surface with normal n.
		// n must be normalized.
		UTIL_GPU_QUAL static vec2<T> reflect(const vec2<T>& a, const vec2<T>& n);
		UTIL_GPU_QUAL static vec2<T> rev_reflect(const vec2<T>& a, const vec2<T>& n);
	};
	
	template<class T> class vec3 {
	public:
		T x;
		T y;
		T z;
		
		UTIL_GPU_QUAL vec3();
		UTIL_GPU_QUAL vec3(double x, double y, double z);
		
		// Vectors are always implicitly convertable to all integer and floating-point types.
		UTIL_GPU_QUAL vec3(const vec3<signed char>& o);
		UTIL_GPU_QUAL vec3(const vec3<signed short>& o);
		UTIL_GPU_QUAL vec3(const vec3<signed int>& o);
		UTIL_GPU_QUAL vec3(const vec3<signed long int>& o);
		UTIL_GPU_QUAL vec3(const vec3<signed long long int>& o);
		
		UTIL_GPU_QUAL vec3(const vec3<unsigned char>& o);
		UTIL_GPU_QUAL vec3(const vec3<unsigned short>& o);
		UTIL_GPU_QUAL vec3(const vec3<unsigned int>& o);
		UTIL_GPU_QUAL vec3(const vec3<unsigned long int>& o);
		UTIL_GPU_QUAL vec3(const vec3<unsigned long long int>& o);
		
		UTIL_GPU_QUAL vec3(const vec3<float>& o);
		UTIL_GPU_QUAL vec3(const vec3<double>& o);
		UTIL_GPU_QUAL vec3(const vec3<long double>& o);
		
		UTIL_GPU_QUAL double mag() const;
		UTIL_GPU_QUAL double sqr_mag() const;
		
		// Returns the yaw of this vector in the range [-M_PI, M_PI).
		// Angles towards the positive y-axis return a positive yaw.
		// Positive z-axis is considered up.
		UTIL_GPU_QUAL double yaw() const;
		
		// Returns the pitch of this vector in the range [-M_PI/2, M_PI/2].
		// Larger values indicate the vector points more towards the positive z-axis.
		UTIL_GPU_QUAL double pitch() const;
		
		UTIL_GPU_QUAL vec3<T> operator+(const vec3<T>& a) const;
		UTIL_GPU_QUAL vec3<T> operator-(const vec3<T>& a) const;
		UTIL_GPU_QUAL vec3<T> operator*(const vec3<T>& a) const;
		UTIL_GPU_QUAL vec3<T> operator/(const vec3<T>& a) const;
		UTIL_GPU_QUAL vec3<T> operator*(double a) const;
		UTIL_GPU_QUAL vec3<T> operator/(double a) const;
		UTIL_GPU_QUAL vec3<T> operator-() const;
		
		UTIL_GPU_QUAL bool operator==(const vec3<T>& a);
		
		// Returns whether this vector is nan. Only returns true if all elements are nan.
		UTIL_GPU_QUAL bool is_nan();
		
		UTIL_GPU_QUAL vec3<T> normalize();
		UTIL_GPU_QUAL vec3<T> normalize(double t);
		
		UTIL_GPU_QUAL static double distance(const vec3<T>& a, const vec3<T>& b);
		UTIL_GPU_QUAL static double sqr_distance(const vec3<T>& a, const vec3<T>& b);
		
		UTIL_GPU_QUAL static double dot(const vec3<T>& a, const vec3<T>& b);
		UTIL_GPU_QUAL static vec3<T> cross(const vec3<T>& a, const vec3<T>& b);
		
		// Reflect the vector a across n.
		// rev_reflect does the same, but also reverses the direction of the reflected vector.
		// Thus, rev_reflect returns the direction vector a is traveling after reflecting off of a surface with normal n.
		// n must be normalized.
		UTIL_GPU_QUAL static vec3<T> reflect(const vec3<T>& a, const vec3<T>& n);
		UTIL_GPU_QUAL static vec3<T> rev_reflect(const vec3<T>& a, const vec3<T>& n);
	};
	
	template<class T> class vec4 {
	public:
		T w;
		T x;
		T y;
		T z;
		
		UTIL_GPU_QUAL vec4<T>();
		UTIL_GPU_QUAL vec4<T>(T w, T x, T y, T z);
		
		// Vectors are always implicitly convertable to all integer and floating-point types.
		UTIL_GPU_QUAL vec4(const vec4<signed char>& o);
		UTIL_GPU_QUAL vec4(const vec4<signed short>& o);
		UTIL_GPU_QUAL vec4(const vec4<signed int>& o);
		UTIL_GPU_QUAL vec4(const vec4<signed long int>& o);
		UTIL_GPU_QUAL vec4(const vec4<signed long long int>& o);
		
		UTIL_GPU_QUAL vec4(const vec4<unsigned char>& o);
		UTIL_GPU_QUAL vec4(const vec4<unsigned short>& o);
		UTIL_GPU_QUAL vec4(const vec4<unsigned int>& o);
		UTIL_GPU_QUAL vec4(const vec4<unsigned long int>& o);
		UTIL_GPU_QUAL vec4(const vec4<unsigned long long int>& o);
		
		UTIL_GPU_QUAL vec4(const vec4<float>& o);
		UTIL_GPU_QUAL vec4(const vec4<double>& o);
		UTIL_GPU_QUAL vec4(const vec4<long double>& o);
		
		UTIL_GPU_QUAL double mag() const;
		UTIL_GPU_QUAL double sqr_mag() const;
		
		UTIL_GPU_QUAL vec4<T> operator+(const vec4<T>& a) const;
		UTIL_GPU_QUAL vec4<T> operator-(const vec4<T>& a) const;
		UTIL_GPU_QUAL vec4<T> operator*(const vec4<T>& a) const;
		UTIL_GPU_QUAL vec4<T> operator/(const vec4<T>& a) const;
		UTIL_GPU_QUAL vec4<T> operator*(double a) const;
		UTIL_GPU_QUAL vec4<T> operator/(double a) const;
		UTIL_GPU_QUAL vec4<T> operator-() const;
		
		UTIL_GPU_QUAL bool operator==(vec4<T> a);
		
		// Returns whether this vector is nan. Only returns true if all elements are nan
		UTIL_GPU_QUAL bool is_nan();
		
		UTIL_GPU_QUAL vec4<T> normalize();
		UTIL_GPU_QUAL vec4<T> normalize(double t);
		
		UTIL_GPU_QUAL static double distance(const vec4<T>& a, const vec4<T>& b);
		UTIL_GPU_QUAL static double sqr_distance(const vec4<T>& a, const vec4<T>& b);
		
		UTIL_GPU_QUAL static double dot(const vec4<T>& a, const vec4<T>& b);
		
		// Reflect the vector a across n.
		// rev_reflect does the same, but also reverses the direction of the reflected vector.
		// Thus, rev_reflect returns the direction vector a is traveling after reflecting off of a surface with normal n.
		// n must be normalized.
		UTIL_GPU_QUAL static vec4<T> reflect(const vec4<T>& a, const vec4<T>& n);
		UTIL_GPU_QUAL static vec4<T> rev_reflect(const vec4<T>& a, const vec4<T>& n);
	};
	
	template<class T> class complex : public vec2<T> {
	public:
		UTIL_GPU_QUAL complex();
		UTIL_GPU_QUAL complex(T r, T i);
		UTIL_GPU_QUAL complex(double theta);
		
		UTIL_GPU_QUAL complex(const vec2<T>&);
		
		// Vectors are always implicitly convertable to all floating-point types.
		UTIL_GPU_QUAL complex(const complex<float>& o);
		UTIL_GPU_QUAL complex(const complex<double>& o);
		UTIL_GPU_QUAL complex(const complex<long double>& o);
		
		UTIL_GPU_QUAL complex<T> operator*(const complex<T>& a) const;
		UTIL_GPU_QUAL complex<T> operator*(double a) const;
		
		UTIL_GPU_QUAL static complex<T> scale(const complex<T>& a, const complex<T>& b);
		
		// Complex conjugation
		UTIL_GPU_QUAL complex<T> operator~() const;
	};
	
	template<class T> class quaternion : public vec4<T> {
	public:
		UTIL_GPU_QUAL quaternion();
		UTIL_GPU_QUAL quaternion(T w, T x, T y, T z);
		UTIL_GPU_QUAL quaternion(const vec3<T>& axis, double theta); // The constructor normalizes the axis for you.
		
		UTIL_GPU_QUAL quaternion(const vec4<T>& a);
		
		// Vectors are always implicitly convertable to all floating-point types.
		UTIL_GPU_QUAL quaternion(const quaternion<float>& o);
		UTIL_GPU_QUAL quaternion(const quaternion<double>& o);
		UTIL_GPU_QUAL quaternion(const quaternion<long double>& o);
		
		UTIL_GPU_QUAL quaternion operator=(const vec4<T>&) const;
		
		UTIL_GPU_QUAL quaternion operator*(const quaternion& a) const; // Hamilton product
		UTIL_GPU_QUAL quaternion operator*(double a) const;
		
		UTIL_GPU_QUAL static quaternion scale(const quaternion& a, const quaternion& b);
		
		// Complex conjugation
		UTIL_GPU_QUAL quaternion operator~() const;
		
		UTIL_GPU_QUAL static quaternion hamilton(const quaternion& a, const quaternion& b);
		UTIL_GPU_QUAL static vec3<T> vhamilton(const quaternion& a, const quaternion& b);
		
		UTIL_GPU_QUAL quaternion& mhamilton(quaternion& a, const quaternion& b);
		
		// Normalize identical to the vecd4 normalize. This version exists so that quaternion::normalize() will return a quaternion.
		UTIL_GPU_QUAL quaternion normalize();
		UTIL_GPU_QUAL quaternion normalize(double t);
		
		// Rotates the passed vector according to the current quaternion about the origin.
		UTIL_GPU_QUAL vec3<T> apply(const vec3<T>& in) const;
		
		// Rotate the given vector theta radians around the given axis or by applying the given quaternion.
		// Use offset to specify a point through which the axis of rotation passes.
		UTIL_GPU_QUAL static vec3<T> rotate(const vec3<T>& in, const vec3<T>& axis_offset, const vec3<T>& axis_dir, double theta);
		UTIL_GPU_QUAL static vec3<T> rotate(const vec3<T>& in, const vec3<T>& axis_offset, const quaternion<T>& r);
		
		// Interpolate between two quaternions in such a way as to produce smooth rotations.
		UTIL_GPU_QUAL static quaternion<T> slerp(const quaternion<T>& a, const quaternion<T>& b, double t); 
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
