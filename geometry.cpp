namespace util {
	void format_tri(vecd3& a, vecd3& b, vecd3& c) {
		// Ensure segment AB is longest.
		double ab = (a-b).sqr_mag();
		double bc = (b-c).sqr_mag();
		double ca = (c-a).sqr_mag();
		if (bc > ab) {
			vecd3 tmp;
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
			vecd3 tmp;
			tmp = c;
			c = b;
			b = tmp;
		}
	}
	
	// AB must be the longest line in the triangle
	vecd3 coll_ray_tri(vecd3 p, vecd3 d, vecd3 a, vecd3 b, vecd3 c) {
//		printf("(%.2lf, %.2lf, %.2lf), (%.2lf, %.2lf, %.2lf), (%.2lf, %.2lf, %.2lf)\n", a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);

		// Calculate the unit normal vector of the plane containing the triangle
		vecd3 n = vecd3::cross(b-a, c-a).normalize();
		
		double denom = vecd3::dot(d, n);
		
		// If the plane and ray are perpendicular, no collision.
		if (denom == 0) {
			return vecd3(NAN, NAN, NAN);
		}
		
		// Calculate the distance from the origin to the nearest point on the plane
		double nd = vecd3::dot(n, a);
		
//		printf("n: (%.4lf, %.4lf, %.4lf), nd: %lf\n", n.x, n.y, n.z, nd);
		
		// Calculate where along the line the collision occurs.
		double t = (nd - vecd3::dot(p, n)) / denom;
		
//		printf("t: %.2lf\n", t);
		
		// If the collision happens at or before the start of the ray, no collision
		if (t <= 0) {
			return vecd3(NAN, NAN, NAN);
		}
		
		vecd3 p_hit = p + d*t;
		
		// Axes defining a space in the triangle's plane.
		// eu & ev are certain to form a right angle
		vecd3 eu = (b-a).normalize();
		vecd3 ev = ((c-a) - eu * vecd3::dot(eu, c-a)).normalize();
		
		// Calculate the plane coordinates of the points of the triangle.
		// a is (0, 0)
		// b is (w, 0)
		// c is (g, h)
		// and w >= g
		double w = vecd3::dot(eu, (b - a));
		double g = vecd3::dot(eu, (c - a));
		double h = vecd3::dot(ev, (c - a));
		
		// Calculate the plane coordinates of p_hit
		double u = vecd3::dot(eu, (p_hit - a));
		double v = vecd3::dot(ev, (p_hit - a));
		
		// Check if (u, v) is not in the triangle.
		if ((u < 0) ||
		    (u > w) ||
		    (v < 0) ||
		    (v > h) ||
		    (u <= g && v > u*h/g) ||
		    (u >= g && v > (w-u) * h / (w-g))) {
			return vecd3(NAN, NAN, NAN);
		}
		
		return p_hit;
	}
}


























