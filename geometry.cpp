namespace util {
	void format_tri(vec3<float>& a, vec3<float>& b, vec3<float>& c) {
		// Ensure segment AB is longest.
		double ab = (a-b).sqr_mag();
		double bc = (b-c).sqr_mag();
		double ca = (c-a).sqr_mag();
		if (bc > ab) {
			vec3<float> tmp;
			if (bc > ca) {
				tmp = a;
				a = c;
				c = tmp;
			}
			else {
				tmp = c;
				c = b;
				b = tmp;
			}
		}
		else if (ca > ab) {
			vec3<float> tmp;
			tmp = c;
			c = b;
			b = tmp;
		}
	}
	
	// AB must be the longest line in the triangle
	vec3<float> coll_ray_tri(vec3<float> p, vec3<float> d, vec3<float> a, vec3<float> b, vec3<float> c) {
//		printf("(%.2lf, %.2lf, %.2lf), (%.2lf, %.2lf, %.2lf), (%.2lf, %.2lf, %.2lf)\n", a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);

		// Calculate the unit normal vector of the plane containing the triangle
		vec3<float> n = vec3<float>::cross(b-a, c-a).normalize();
		
		double denom = vec3<float>::dot(d, n);
		
		// If the plane and ray are perpendicular, no collision.
		if (denom == 0) {
			return vec3<float>(NAN, NAN, NAN);
		}
		
		// Calculate the distance from the origin to the nearest point on the plane
		double nd = vec3<float>::dot(n, a);
		
//		printf("n: (%.4lf, %.4lf, %.4lf), nd: %lf\n", n.x, n.y, n.z, nd);
		
		// Calculate where along the line the collision occurs.
		double t = (nd - vec3<float>::dot(p, n)) / denom;
		
//		printf("t: %.2lf\n", t);
		
		// If the collision happens at or before the start of the ray, no collision
		if (t <= 0) {
			return vec3<float>(NAN, NAN, NAN);
		}
		
		vec3<float> p_hit = p + d*t;
		
		// Axes defining a space in the triangle's plane.
		// eu & ev are certain to form a right angle
		vec3<float> eu = (b-a).normalize();
		vec3<float> ev = ((c-a) - eu * vec3<float>::dot(eu, c-a)).normalize();
		
		// Calculate the plane coordinates of the points of the triangle.
		// a is (0, 0)
		// b is (w, 0)
		// c is (g, h)
		// and w >= g
		double w = vec3<float>::dot(eu, (b - a));
		double g = vec3<float>::dot(eu, (c - a));
		double h = vec3<float>::dot(ev, (c - a));
		
		// Calculate the plane coordinates of p_hit
		double u = vec3<float>::dot(eu, (p_hit - a));
		double v = vec3<float>::dot(ev, (p_hit - a));
		
		// Check if (u, v) is not in the triangle.
		if ((u < 0) ||
		    (u > w) ||
		    (v < 0) ||
		    (v > h) ||
		    (u <= g && v > u*h/g) ||
		    (u >= g && v > (w-u) * h / (w-g))) {
			return vec3<float>(NAN, NAN, NAN);
		}
		
		return p_hit;
	}
}


























