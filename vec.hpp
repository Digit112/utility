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
	
	/// A class representing 2D vectors. Implicit conversions between types with differing template parameters are defined.
	/** IMPORTANT: Operations between vec2 objects with different template parameters
	*   may return unexpected results. The right operand will be converted to the type of the left operand.
	*   
	*   Implicit conversion to the following template parameter types are allowed:
	*   - `signed char`
	*   - `signed short`
	*   - `signed int`
	*   - `signed long int`
	*   - `signed long long int`
	*   - `unsigned char`
	*   - `unsigned short`
	*   - `unsigned int`
	*   - `unsigned long int`
	*   - `unsigned long long int`
	*   - `float`
	*   - `double`
	*   - `long double`
	*/
	template<class T> class vec2 {
	public:
		T x;
		T y;
		
		vec2();
		vec2(T x, T y);
		
		// Vectors are always implicitly convertable to all integer and floating-point types.
		vec2(const vec2<signed char>& o);
		vec2(const vec2<signed short>& o);
		vec2(const vec2<signed int>& o);
		vec2(const vec2<signed long int>& o);
		vec2(const vec2<signed long long int>& o);
		
		vec2(const vec2<unsigned char>& o);
		vec2(const vec2<unsigned short>& o);
		vec2(const vec2<unsigned int>& o);
		vec2(const vec2<unsigned long int>& o);
		vec2(const vec2<unsigned long long int>& o);
		
		vec2(const vec2<float>& o);
		vec2(const vec2<double>& o);
		vec2(const vec2<long double>& o);
		
		// Returns the magnitude of this vector
		double mag() const;
		// Returns the squared magnitude of this vector
		double sqr_mag() const;
		
		// Returns the argument of the vector.
		// I.e. the angle counter-clockwise from the positive x-axis to this vector.
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
		
		// Returns a normalized version of this vector.
		vec2<T> normalize() const;
		
		// Returns this vector normalized to a specific length.
		vec2<T> normalize(double t) const;
		
		static vec2<T> lerp(const vec2<T>& a, const vec2<T>& b, double t);
		
		static double distance(const vec2<T>& a, const vec2<T>& b);
		static double sqr_distance(const vec2<T>& a, const vec2<T>& b);
		
		// Returns the Dot Product of two vectors
		static double dot(const vec2<T>& a, const vec2<T>& b);
		
		// Reflect the vector a across n.
		// rev_reflect does the same, but also reverses the direction of the reflected vector.
		// Thus, rev_reflect returns the direction vector a is traveling after reflecting off of a surface with normal n.
		// n must be normalized.
		static vec2<T> reflect(const vec2<T>& a, const vec2<T>& n);
		static vec2<T> rev_reflect(const vec2<T>& a, const vec2<T>& n);
	};
	
	/// A class representing 3D vectors. Implicit conversions between types with differing template parameters are defined.
	/** IMPORTANT: Operations between vec3 objects with different template parameters
	*   may return unexpected results. The right operand will be converted to the type of the left operand.
	*   
	*   Implicit conversion to the following template parameter types are allowed:
	*   - `signed char`
	*   - `signed short`
	*   - `signed int`
	*   - `signed long int`
	*   - `signed long long int`
	*   - `unsigned char`
	*   - `unsigned short`
	*   - `unsigned int`
	*   - `unsigned long int`
	*   - `unsigned long long int`
	*   - `float`
	*   - `double`
	*   - `long double`
	*/
	template<class T> class vec3 {
	public:
		T x;
		T y;
		T z;
		
		vec3();
		vec3(double x, double y, double z);
		
		// Vectors are always implicitly convertable to all integer and floating-point types.
		vec3(const vec3<signed char>& o);
		vec3(const vec3<signed short>& o);
		vec3(const vec3<signed int>& o);
		vec3(const vec3<signed long int>& o);
		vec3(const vec3<signed long long int>& o);
		
		vec3(const vec3<unsigned char>& o);
		vec3(const vec3<unsigned short>& o);
		vec3(const vec3<unsigned int>& o);
		vec3(const vec3<unsigned long int>& o);
		vec3(const vec3<unsigned long long int>& o);
		
		vec3(const vec3<float>& o);
		vec3(const vec3<double>& o);
		vec3(const vec3<long double>& o);
		
		double mag() const;
		double sqr_mag() const;
		
		// Returns the yaw of this vector in the range [-M_PI, M_PI).
		// Angles towards the positive y-axis return a positive yaw.
		// Positive z-axis is considered up.
		double yaw() const;
		
		// Returns the pitch of this vector in the range [-M_PI/2, M_PI/2].
		// Larger values indicate the vector points more towards the positive z-axis.
		double pitch() const;
		
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
		
		// Returns a normalized version of this vector.
		vec3<T> normalize() const;
		
		// Returns this vector normalized to a specific length.
		vec3<T> normalize(double t) const;
		
		static vec3<T> lerp(const vec3<T>& a, const vec3<T>& b, double t);
		
		static double distance(const vec3<T>& a, const vec3<T>& b);
		static double sqr_distance(const vec3<T>& a, const vec3<T>& b);
		
		static double dot(const vec3<T>& a, const vec3<T>& b);
		static vec3<T> cross(const vec3<T>& a, const vec3<T>& b);
		
		// Reflect the vector a across n.
		// rev_reflect does the same, but also reverses the direction of the reflected vector.
		// Thus, rev_reflect returns the direction vector a is traveling after reflecting off of a surface with normal n.
		// n must be normalized.
		static vec3<T> reflect(const vec3<T>& a, const vec3<T>& n);
		static vec3<T> rev_reflect(const vec3<T>& a, const vec3<T>& n);
	};
	
	/// A class representing 4D vectors. Implicit conversions between types with differing template parameters are defined.
	/** The components are taken to be in the order w, x, y, z.
	*   IMPORTANT: Operations between vec4 objects with different template parameters
	*   may return unexpected results. The right operand will be converted to the type of the left operand.
	*   
	*   Implicit conversion to the following template parameter types are allowed:
	*   - `signed char`
	*   - `signed short`
	*   - `signed int`
	*   - `signed long int`
	*   - `signed long long int`
	*   - `unsigned char`
	*   - `unsigned short`
	*   - `unsigned int`
	*   - `unsigned long int`
	*   - `unsigned long long int`
	*   - `float`
	*   - `double`
	*   - `long double`
	*/
	template<class T> class vec4 {
	public:
		T w;
		T x;
		T y;
		T z;
		
		vec4<T>();
		vec4<T>(T w, T x, T y, T z);
		
		// Vectors are always implicitly convertable to all integer and floating-point types.
		vec4(const vec4<signed char>& o);
		vec4(const vec4<signed short>& o);
		vec4(const vec4<signed int>& o);
		vec4(const vec4<signed long int>& o);
		vec4(const vec4<signed long long int>& o);
		
		vec4(const vec4<unsigned char>& o);
		vec4(const vec4<unsigned short>& o);
		vec4(const vec4<unsigned int>& o);
		vec4(const vec4<unsigned long int>& o);
		vec4(const vec4<unsigned long long int>& o);
		
		vec4(const vec4<float>& o);
		vec4(const vec4<double>& o);
		vec4(const vec4<long double>& o);
		
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
		
		// Returns a normalized version of this vector.
		vec4<T> normalize() const;
		
		// Returns this vector normalized to a specific length.
		vec4<T> normalize(double t) const;
		
		static vec4<T> lerp(const vec4<T>& a, const vec4<T>& b, double t);
		
		static double distance(const vec4<T>& a, const vec4<T>& b);
		static double sqr_distance(const vec4<T>& a, const vec4<T>& b);
		
		static double dot(const vec4<T>& a, const vec4<T>& b);
		
		// Reflect the vector a across n.
		// rev_reflect does the same, but also reverses the direction of the reflected vector.
		// Thus, rev_reflect returns the direction vector a is traveling after reflecting off of a surface with normal n.
		// n must be normalized.
		static vec4<T> reflect(const vec4<T>& a, const vec4<T>& n);
		static vec4<T> rev_reflect(const vec4<T>& a, const vec4<T>& n);
	};
	
	/// A class representing complex numbers.
	/** Complex numbers serve to represent rotations in 2D, among other things.
	*   
	*   Implicit conversion to the following template parameter types are allowed:
	*   - `float`
	*   - `double`
	*   - `long double` */
	template<class T> class complex : public vec2<T> {
	public:
		complex();
		complex(T r, T i);
		complex(double theta);
		
		complex(const vec2<T>&);
		
		// Vectors are always implicitly convertable to all floating-point types.
		complex(const complex<float>& o);
		complex(const complex<double>& o);
		complex(const complex<long double>& o);
		
		complex<T> operator*(const complex<T>& a) const;
		complex<T> operator*(double a) const;
		
		static complex<T> scale(const complex<T>& a, const complex<T>& b);
		
		// Complex conjugation
		complex<T> operator~() const;
	};
	
	/// A class representing quaternions.
	/** Quaternions serve to represent rotations in 3D, among other things.
	*   
	*   Implicit conversion to the following template parameter types are allowed:
	*   - `float`
	*   - `double`
	*   - `long double` */
	template<class T> class quaternion : public vec4<T> {
	public:
		quaternion();
		quaternion(T w, T x, T y, T z);
		quaternion(const vec3<T>& axis, double theta); // The constructor normalizes the axis for you.
		
		quaternion(const vec4<T>& a);
		
		// Vectors are always implicitly convertable to all floating-point types.
		quaternion(const quaternion<float>& o);
		quaternion(const quaternion<double>& o);
		quaternion(const quaternion<long double>& o);
		
		quaternion operator=(const vec4<T>&) const;
		
		quaternion operator*(const quaternion& a) const; // Hamilton product
		quaternion operator*(double a) const;
		
		static quaternion scale(const quaternion& a, const quaternion& b);
		
		// Complex conjugation
		quaternion operator~() const;
		
		static quaternion hamilton(const quaternion& a, const quaternion& b);
		static vec3<T> vhamilton(const quaternion& a, const quaternion& b);
		
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
