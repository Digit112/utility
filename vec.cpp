namespace util {
	/* ---- vec2 ---- */
	
	template<class T> vec2<T>::vec2() : x(0), y(0) {}
	template<class T> vec2<T>::vec2(T x, T y) : x(x), y(y) {}
	
	template<class T> vec2<T>::vec2(const vec2<signed char>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<signed short>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<signed int>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<signed long int>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<signed long long int>& o) : x(o.x), y(o.y) {}
	
	template<class T> vec2<T>::vec2(const vec2<unsigned char>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<unsigned short>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<unsigned int>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<unsigned long int>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<unsigned long long int>& o) : x(o.x), y(o.y) {}
	
	template<class T> vec2<T>::vec2(const vec2<float>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<double>& o) : x(o.x), y(o.y) {}
	template<class T> vec2<T>::vec2(const vec2<long double>& o) : x(o.x), y(o.y) {}
	
	template<class T> double vec2<T>::mag() const {
		return sqrt(x*x + y*y);
	}
	
	template<class T> double vec2<T>::sqr_mag() const {
		return x*x + y*y;
	}
	
	template<class T> double vec2<T>::arg() {
		return M_PI - atan2(y, -x);
	}
	
	template<class T> vec2<T> vec2<T>::operator+(const vec2<T>& a) const {
		return vec2(x+a.x, y+a.y);
	}
	template<class T> vec2<T> vec2<T>::operator-(const vec2<T>& a) const {
		return vec2(x-a.x, y-a.y);
	}
	template<class T> vec2<T> vec2<T>::operator*(const vec2<T>& a) const {
		return vec2(x*a.x, y*a.y);
	}
	template<class T> vec2<T> vec2<T>::operator/(const vec2<T>& a) const {
		return vec2(x/a.x, y/a.y);
	}
	template<class T> vec2<T> vec2<T>::operator*(double a) const {
		return vec2(x*a, y*a);
	}
	template<class T> vec2<T> vec2<T>::operator/(double a) const {
		return vec2(x/a, y/a);
	}
	template<class T> vec2<T> vec2<T>::operator-() const {
		return vec2(-x, -y);
	}
	
	template<class T> bool vec2<T>::operator==(const vec2<T>& a) const {
		return x == a.x && y == a.y;
	}
	
	template<class T> bool vec2<T>::is_nan() const {
		return isnan(x) && isnan(y);
	}
	
	template<class T> vec2<T> vec2<T>::normalize() const {
		double m = mag();
		return vec2(x/m, y/m);
	}
	
	template<class T> vec2<T> vec2<T>::normalize(double t) const {
		double m = mag() / t;
		return vec2(x/m, y/m);
	}
	
	template<class T> vec2<T> vec2<T>::lerp(const vec2<T>& a, const vec2<T>& b, double t) {
		return vec2<T>(
			a.x + (b.x - a.x)*t,
			a.y + (b.y - a.y)*t
		);
	}
	
	template<class T> double vec2<T>::distance(const vec2<T>& a, const vec2<T>& b) {
		double dx = a.x - b.x;
		double dy = a.y - b.y;
		
		return sqrt(dx*dx + dy*dy);
	}
	
	template<class T> double vec2<T>::sqr_distance(const vec2<T>& a, const vec2<T>& b) {
		double dx = a.x - b.x;
		double dy = a.y - b.y;
		
		return dx*dx + dy*dy;
	}
	
	template<class T> double vec2<T>::dot(const vec2<T>& a, const vec2<T>& b) {
		return a.x*b.x + a.y*b.y;
	}
	
	template<class T> vec2<T> vec2<T>::reflect(const vec2<T>& a, const vec2<T>& n) {
		return n * vec2<T>::dot(a, n) * 2 - a;
	}
	
	template<class T> vec2<T> vec2<T>::rev_reflect(const vec2<T>& a, const vec2<T>& n) {
		return a - n * vec2<T>::dot(a, n) * 2;
	}
	
	/* ---- vec3 ---- */
	
	template<class T> vec3<T>::vec3() : x(0), y(0), z(0) {}
	template<class T> vec3<T>::vec3(double x, double y, double z) : x(x), y(y), z(z) {}
	
	template<class T> vec3<T>::vec3(const vec3<signed char>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<signed short>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<signed int>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<signed long int>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<signed long long int>& o) : x(o.x), y(o.y), z(o.z) {}
	
	template<class T> vec3<T>::vec3(const vec3<unsigned char>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<unsigned short>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<unsigned int>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<unsigned long int>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<unsigned long long int>& o) : x(o.x), y(o.y), z(o.z) {}
	
	template<class T> vec3<T>::vec3(const vec3<float>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<double>& o) : x(o.x), y(o.y), z(o.z) {}
	template<class T> vec3<T>::vec3(const vec3<long double>& o) : x(o.x), y(o.y), z(o.z) {}
	
	template<class T> double vec3<T>::mag() const {
		return sqrt(x*x + y*y + z*z);
	}
	
	template<class T> double vec3<T>::sqr_mag() const {
		return x*x + y*y + z*z;
	}
	
	template<class T> double vec3<T>::yaw() const {
		return atan2(y, x);
	}
	
	template<class T> double vec3<T>::pitch() const {
		return atan(z / sqrt(x*x + y*y));
	}
	
	template<class T> vec3<T> vec3<T>::operator+(const vec3<T>& a) const {
		return vec3<T>(x+a.x, y+a.y, z+a.z);
	}
	template<class T> vec3<T> vec3<T>::operator-(const vec3<T>& a) const {
		return vec3<T>(x-a.x, y-a.y, z-a.z);
	}
	template<class T> vec3<T> vec3<T>::operator*(const vec3<T>& a) const {
		return vec3<T>(x*a.x, y*a.y, z*a.z);
	}
	template<class T> vec3<T> vec3<T>::operator/(const vec3<T>& a) const {
		return vec3<T>(x/a.x, y/a.y, z/a.z);
	}
	template<class T> vec3<T> vec3<T>::operator*(double a) const {
		return vec3<T>(x*a, y*a, z*a);
	}
	template<class T> vec3<T> vec3<T>::operator/(double a) const {
		return vec3<T>(x/a, y/a, z/a);
	}
	template<class T> vec3<T> vec3<T>::operator-() const {
		return vec3<T>(-x, -y, -z);
	}
	
	template<class T> bool vec3<T>::operator==(const vec3<T>& a) {
		return x == a.x && y == a.y && z == a.z;
	}
	
	template<class T> bool vec3<T>::is_nan() {
		return isnan(x) && isnan(y) && isnan(z);
	}
	
	template<class T> vec3<T> vec3<T>::normalize() const {
		double m = mag();
		return vec3<T>(x/m, y/m, z/m);
	}
	template<class T> vec3<T> vec3<T>::normalize(double t) const {
		double m = mag() / t;
		return vec3<T>(x/m, y/m, z/m);
	}
	
	template<class T> vec3<T> vec3<T>::lerp(const vec3<T>& a, const vec3<T>& b, double t) {
		return vec3<T>(
			a.x + (b.x - a.x)*t,
			a.y + (b.y - a.y)*t,
			a.z + (b.z - a.z)*t
		);
	}
	
	template<class T> double vec3<T>::distance(const vec3<T>& a, const vec3<T>& b) {
		double dx = a.x - b.x;
		double dy = a.y - b.y;
		double dz = a.z - b.z;
		
		return sqrt(dx*dx + dy*dy + dz*dz);
	}
	
	template<class T> double vec3<T>::sqr_distance(const vec3<T>& a, const vec3<T>& b) {
		double dx = a.x - b.x;
		double dy = a.y - b.y;
		double dz = a.z - b.z;
		
		return dx*dx + dy*dy + dz*dz;
	}
	
	template<class T> double vec3<T>::dot(const vec3<T>& a, const vec3<T>& b) {
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}
	
	template<class T> vec3<T> vec3<T>::cross(const vec3<T>& a, const vec3<T>& b) {
		return vec3<T>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	}
	
	template<class T> vec3<T> vec3<T>::reflect(const vec3<T>& a, const vec3<T>& n) {
		return n * vec3<T>::dot(a, n) * 2 - a;
	}
	
	template<class T> vec3<T> vec3<T>::rev_reflect(const vec3<T>& a, const vec3<T>& n) {
		return a - n * vec3<T>::dot(a, n) * 2;
	}
	
	/* ---- vecd4 ---- */
	
	template<class T> vec4<T>::vec4() : w(0), x(0), y(0), z(0) {}
	template<class T> vec4<T>::vec4(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}
	
	template<class T> vec4<T>::vec4(const vec4<signed char>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<signed short>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<signed int>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<signed long int>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<signed long long int>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	
	template<class T> vec4<T>::vec4(const vec4<unsigned char>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<unsigned short>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<unsigned int>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<unsigned long int>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<unsigned long long int>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	
	template<class T> vec4<T>::vec4(const vec4<float>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<double>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	template<class T> vec4<T>::vec4(const vec4<long double>& o) : w(o.w), x(o.x), y(o.y), z(o.z) {}
	
	template<class T> double vec4<T>::mag() const {
		return sqrt(w*w + x*x + y*y + z*z);
	}
	
	template<class T> double vec4<T>::sqr_mag() const {
		return w*w + x*x + y*y + z*z;
	}
	
	template<class T> vec4<T> vec4<T>::operator+(const vec4<T>& a) const {
		return vec4<T>(w+a.w, x+a.x, y+a.y, z+a.z);
	}
	template<class T> vec4<T> vec4<T>::operator-(const vec4<T>& a) const {
		return vec4<T>(w-a.w, x-a.x, y-a.y, z-a.z);
	}
	template<class T> vec4<T> vec4<T>::operator*(const vec4<T>& a) const {
		return vec4<T>(w*a.w, x*a.x, y*a.y, z*a.z);
	}
	template<class T> vec4<T> vec4<T>::operator/(const vec4<T>& a) const {
		return vec4<T>(w/a.w, x/a.x, y/a.y, z/a.z);
	}
	template<class T> vec4<T> vec4<T>::operator*(double a) const {
		return vec4<T>(w*a, x*a, y*a, z*a);
	}
	template<class T> vec4<T> vec4<T>::operator/(double a) const {
		return vec4<T>(w/a, x/a, y/a, z/a);
	}
	template<class T> vec4<T> vec4<T>::operator-() const {
		return vec4<T>(-w, -x, -y, -z);
	}
	
	template<class T> bool vec4<T>::operator==(vec4<T> a) {
		return w == a.w && x == a.x && y == a.y && z == a.z;
	}
	
	template<class T> bool vec4<T>::is_nan() {
		return isnan(w) && isnan(x) && isnan(y) && isnan(z);
	}
	
	template<class T> vec4<T> vec4<T>::normalize() const {
		double m = mag();
		return vec4<T>(w/m, x/m, y/m, z/m);
	}
	template<class T> vec4<T> vec4<T>::normalize(double t) const {
		double m = mag() / t;
		return vec4<T>(w/m, x/m, y/m, z/m);
	}
	
	template<class T> vec4<T> vec4<T>::lerp(const vec4<T>& a, const vec4<T>& b, double t) {
		return vec3<T>(
			a.w + (b.w - a.w)*t,
			a.x + (b.x - a.x)*t,
			a.y + (b.y - a.y)*t,
			a.z + (b.z - a.z)*t
		);
	}
	
	template<class T> double vec4<T>::distance(const vec4<T>& a, const vec4<T>& b) {
		double dw = a.w - b.w;
		double dx = a.x - b.x;
		double dy = a.y - b.y;
		double dz = a.z - b.z;
		
		return sqrt(dw*dw + dx*dx + dy*dy + dz*dz);
	}
	
	template<class T> double vec4<T>::sqr_distance(const vec4<T>& a, const vec4<T>& b) {
		double dw = a.w - b.w;
		double dx = a.x - b.x;
		double dy = a.y - b.y;
		double dz = a.z - b.z;
		
		return dw*dw + dx*dx + dy*dy + dz*dz;
	}
	
	template<class T> double vec4<T>::dot(const vec4<T>& a, const vec4<T>& b) {
		return a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z;
	}
	
	template<class T> vec4<T> vec4<T>::reflect(const vec4<T>& a, const vec4<T>& n) {
		return n * vec4<T>::dot(a, n) * 2 - a;
	}
	
	template<class T> vec4<T> vec4<T>::rev_reflect(const vec4<T>& a, const vec4<T>& n) {
		return a - n * vec4<T>::dot(a, n) * 2;
	}
	
	/* ---- complex ---- */
	
	template<class T> complex<T>::complex() : vec2<T>() {}
	template<class T> complex<T>::complex(T r, T i) : vec2<T>(r, i) {}
	template<class T> complex<T>::complex(double theta) : vec2<T>(cos(theta), sin(theta)) {}
	
	template<class T> complex<T>::complex(const vec2<T>& a) : vec2<T>(a) {}
	template<class T> complex<T>::complex(const complex<float>& o) : vec2<T>(o.x, o.y) {}
	template<class T> complex<T>::complex(const complex<double>& o) : vec2<T>(o.x, o.y) {}
	template<class T> complex<T>::complex(const complex<long double>& o) : vec2<T>(o.x, o.y) {}
	
	template<class T> complex<T> complex<T>::operator*(const complex<T>& a) const {
		return complex<T>(this->x*a.x - this->y*a.y, this->x*a.y + this->y*a.x);
	}
	
	template<class T> complex<T> complex<T>::operator*(double a) const {
		return complex<T>(this->x*a, this->y*a);
	}
	
	template<class T> complex<T> complex<T>::scale(const complex<T>& a, const complex<T>& b) {
		return complex<T>(a.x*b.x, a.y*b.y);
	}
	
	template<class T> complex<T> complex<T>::operator~() const {
		return complex<T>(this->x, -this->y);
	}
	
	/* ---- quaternion ---- */
	
	template<class T> quaternion<T>::quaternion() : vec4<T>() {}
	template<class T> quaternion<T>::quaternion(T w, T x, T y, T z) : vec4<T>(w, x, y, z) {}

	template<class T> quaternion<T>::quaternion(const vec3<T>& axis, double theta) {
		axis = axis.normalize();
		double s = sin(theta/2);
		this->w = cos(theta/2);
		this->x = axis.x * s;
		this->y = axis.y * s;
		this->z = axis.z * s;
	}
	
	template<class T> quaternion<T>::quaternion(const vec4<T>& a) : vec4<T>(a) {}
	
	template<class T> quaternion<T>::quaternion(const quaternion<float>& o) : vec4<T>(o.w, o.x, o.y, o.z) {}
	template<class T> quaternion<T>::quaternion(const quaternion<double>& o) : vec4<T>(o.w, o.x, o.y, o.z) {}
	template<class T> quaternion<T>::quaternion(const quaternion<long double>& o) : vec4<T>(o.w, o.x, o.y, o.z) {}
	
	template<class T> quaternion<T> quaternion<T>::operator*(const quaternion<T>& a) const {
		return quaternion<T>(
			this->w*a.w - this->x*a.x - this->y*a.y - this->z*a.z,
			this->w*a.x + this->x*a.w + this->y*a.z - this->z*a.y,
			this->w*a.y - this->x*a.z + this->y*a.w + this->z*a.x,
			this->w*a.z + this->x*a.y - this->y*a.x + this->z*a.w
		);
	}
	
	template<class T> quaternion<T> quaternion<T>::operator*(double a) const {
		return quaternion(this->w*a, this->x*a, this->y*a, this->z*a);
	}
	
	template<class T> quaternion<T> quaternion<T>::scale(const quaternion<T>& a, const quaternion<T>& b) {
		return quaternion<T>(a.w*b.w, a.x*b.x, a.y*b.y, a.z*b.z);
	}
	
	template<class T> quaternion<T> quaternion<T>::operator=(const vec4<T>& a) const {
		return quaternion<T>(a.w, a.x, a.y, a.z);
	}
	
	template<class T> quaternion<T> quaternion<T>::operator~() const {
		return quaternion<T>(this->w, -this->x, -this->y, -this->z);
	}
	
	template<class T> quaternion<T> quaternion<T>::normalize() {
		double m = this->mag();
		return quaternion<T>(this->w/m, this->x/m, this->y/m, this->z/m);
	}
	
	template<class T> quaternion<T> quaternion<T>::normalize(double t) {
		double m = this->mag() / t;
		return quaternion<T>(this->w/m, this->x/m, this->y/m, this->z/m);
	}
	
	template<class T> quaternion<T> quaternion<T>::hamilton(const quaternion<T>& a, const quaternion<T>& b) {
		return quaternion<T>(
			a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z,
			a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
			a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
			a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w
		);
	}
	
	template<class T> vec3<T> quaternion<T>::vhamilton(const quaternion<T>& a, const quaternion<T>& b) {
		return vecd3(
			a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
			a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
			a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w
		);
	}
	
	template<class T> quaternion<T>& quaternion<T>::mhamilton(quaternion<T>& a, const quaternion<T>& b) {
		a.w = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z;
		a.x = a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y;
		a.y = a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x;
		a.z = a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w;
		return a;
	}
	
	template<class T> vec3<T> quaternion<T>::apply(const vec3<T>& in) const {
		return vhamilton(
			hamilton(
				*this,
				quaternion<T>(0, in.x, in.y, in.z)
			),
			quaternion<T>(this->w, -this->x, -this->y, -this->z)
		);
	}
	
	template<class T> vec3<T> quaternion<T>::rotate(const vec3<T>& in, const vec3<T>& axis_offset, const vec3<T>& axis_dir, double theta) {
		in = in - axis_offset;
		in = quaternion<T>(axis_dir, theta).apply(in);
		return in + axis_offset;
	}
	
	template<class T> vec3<T> quaternion<T>::rotate(const vec3<T>& in, const vec3<T>& axis_offset, const quaternion<T>& r) {
		in = in - axis_offset;
		in = r.apply(in);
		return in + axis_offset;
	}
	
	template<class T> quaternion<T> quaternion<T>::slerp(const quaternion<T>& a, const quaternion<T>& b, double t) {
		double dot = quaternion<T>::dot(a, b);
		if (dot < 0) {
			a = -a;
			dot = -dot;
		}
		
		const double DOT_THRESHOLD = 0.995;
		if (dot > DOT_THRESHOLD) {
			quaternion<T> out = a + (b-a)*t;
			out = out.normalize();
			return out;
		}
		
		double theta_0 = acos(dot);
		double theta = theta_0 * t;
		
		double sin_theta = sin(theta);
		double sin_theta_0 = sin(theta_0);
		
		double s0 = cos(theta) - dot * sin_theta / sin_theta_0;
		double s1 = sin_theta / sin_theta_0;
		
		return (a*s0) + (b*s1);
	}
}