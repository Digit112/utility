namespace util {
	/* ---- rng_xoshiro_starstar ---- */
	
	/// Initialize the random number generator with a seed.
	void rng_xoshiro_starstar::init(uint32_t sd) {
		seed[0] = hashing::FNV_32(sd);
		seed[1] = hashing::FNV_32(seed[0]);
		seed[2] = hashing::FNV_32(seed[1]);
		seed[3] = hashing::FNV_32(seed[2]);
	}
	
	/// Get a random integer in the range -2^31 to 2^31-1, inclusive.
	int rng_xoshiro_starstar::random_int() {
		/*  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

		To the extent possible under law, the author has dedicated all copyright
		and related and neighboring rights to this software to the public domain
		worldwide. This software is distributed without any warranty.

		See <http://creativecommons.org/publicdomain/zero/1.0/>
		Original <http://xoshiro.di.unimi.it/xoshiro128starstar.c>  */
		
		unsigned int temp = seed[0] * 5;
		unsigned int result = (temp << 7) | (temp >> 25);
		
		unsigned int t = seed[1] << 9;
		
		seed[2] ^= seed[0];
		seed[3] ^= seed[1];
		seed[1] ^= seed[2];
		seed[0] ^= seed[3];
		
		temp = seed[3];
		seed[3] = (temp << 11) | (temp >> 21);
		
		return (int) result;
	}
	
	/// Get a random floating-point value in the range 0.0 to 1.0.
	float rng_xoshiro_starstar::random_val() {
		return (float) random_int() / 0xFFFFFFFF + 0.5;
	}
	
	/* ---- hashing ---- */
	
	/// FNV32 hash of a 32-bit integer.
	uint32_t hashing::FNV_32(uint32_t seed) {
		uint32_t hash = 2166136261;
		for (int i = 0; i < 4; i++) {
			hash *= 16777619;
			hash ^= (unsigned char) (seed >> (i*8));
		}
		return hash;
	}
	
	/// FNV32 hash of a 64-bit integer.
	uint32_t hashing::FNV_32(uint64_t seed) {
		uint32_t hash = 2166136261;
		for (int i = 0; i < 8; i++) {
			hash *= 16777619;
			hash ^= (unsigned char) (seed >> (i*8));
		}
		return hash;
	}
	
	/// FNV32 hash of a null-terminated string.
	uint32_t hashing::FNV_32(const char* seed) {
		uint32_t hash = 2166136261;
		for (int i = 0; seed[i] != '\0'; i++) {
			hash *= 16777619;
			hash ^= seed[i];
		}
		return hash;
	}
	
	/* ---- pattern2 ---- */
	
	/// Create an empty pattern.
	pattern2::pattern2() : width(0), height(0), data(NULL) {}
	
	/// Deep-copy a pattern.
	pattern2::pattern2(const pattern2& c) : width(c.width), height(c.height) {
		data = new float[width*height];
		for (int i = 0; i < width*height; i++) {
			data[i] = c.data[i];
		}
	}
	
	/// Create a pattern with the given width and height. Cells are not initialized.
	pattern2::pattern2(int width, int height) : width(width), height(height) {
		data = new float[width*height];
	}
	
	/// Create a pattern with the given width and height and initialize all cells to the given fill value.
	pattern2::pattern2(int width, int height, float fill) : width(width), height(height) {
		data = new float[width*height];
		for (int i = 0; i < width*height; i++) {
			data[i] = fill;
		}
	}
	
	/// Deep copy another pattern.
	void pattern2::operator=(const pattern2& c) {
		if (data != NULL) {
			delete[] data;
		}
		
		width = c.width;
		height = c.height;
		data = new float[width*height];
		for (int i = 0; i < width*height; i++) {
			data[i] = c.data[i];
		}
	}
	
	/// Save this pattern as a ppm.
	/** Values of 0 are black and 1 are white. Values outside this range may produce unexpected results.
	*   Use fit_values() or clamp() to ensure that values are in the appropriate range. */
	void pattern2::saveppm(const char* fn) {
		FILE* fp = fopen(fn, "wb+");
		
		char* buff = new char[256];
		sprintf(buff, "P5\n%d %d\n255\n", width, height);
		fwrite(buff, 1, strlen(buff), fp);
		delete[] buff;
		
		unsigned short* out = new unsigned short[width*height];
		unsigned short temp;
		for (int i = 0; i < width*height; i++) {
			temp = floor(data[i] * 255.9);
			// Reverse endianness
			out[i] = (temp << 8) | (temp >> 8);
		}
		fwrite(out, 2, width*height, fp);
		delete[] out;
		
		fclose(fp);
	}
	
	/// Fill the pattern with the passed value.
	void pattern2::fill(float val) {
		for (int i = 0; i < width*height; i++) {
			data[i] = val;
		}
	}
	
	/// Add the passed value to each cell.
	void pattern2::add(float val) {
		for (int i = 0; i < width*height; i++) {
			data[i] += val;
		}
	}
	
	/// Multiply each cell by the passed value.
	void pattern2::scale(float val) {
		for (int i = 0; i < width*height; i++) {
			data[i] *= val;
		}
	}
	
	/// Paint the passed pattern on top of this pattern at the given location and with the given opacity.
	/** The passed x, y coordinates specify the location on this pattern where the other pattern's upper-left corner will appear.
	*   The passed pattern will be cropped as needed to ensure that it is not painted outside the bounds of this pattern.
	*   E.g., you can paint a 100x100 pattern over a 10x10 pattern without issue.
	*   The opacity is in the range 0 to 1. An opacity of 1 overwrites this pattern entirely with the new one.
	*   Opacity values less than 1 use a weighted average of the two patterns to perform blending. The opacity is not clamped. */
	void pattern2::paint(pattern2 p, float opacity, int x, int y) {
		int Mx = x + p.width;
		if (width < Mx) Mx = width;
		int My = y + p.height;
		if (height < My) My = height;
		
		float myop = 1 - opacity;
		
		int x0; int x1; int y0; int y1; int rowc0; int rowc1;
		for (y0 = 0, y1 = y; y1 < My; y1++) {
			rowc0 = p.width*y0;
			rowc1 = width*y1;
			
			for (x0 = 0, x1 = x; x1 < Mx; x1++) {
				data[rowc1+x1] = myop*data[rowc1+x1] + opacity*p.data[rowc0+x0];
				x0++;
			}
			y0++;
		}
	}
	
	/// The same as paint(), but adds the corresponding elements instead of blending them.
	void pattern2::add(pattern2 p, int x, int y) {
		int Mx = x + p.width;
		if (width < Mx) Mx = width;
		int My = y + p.height;
		if (height < My) My = height;
		
		int x0; int x1; int y0; int y1; int rowc0; int rowc1;
		for (y0 = 0, y1 = y; y1 < My; y1++) {
			rowc0 = p.width*y0;
			rowc1 = width*y1;
			
			for (x0 = 0, x1 = x; x1 < Mx; x1++) {
				data[rowc1+x1] = data[rowc1+x1] + p.data[rowc0+x0];
				x0++;
			}
			y0++;
		}
	}
	
	/// The same as paint(), but multiplies the corresponding elements instead of blending them.
	void pattern2::scale(pattern2 p, int x, int y) {
		int Mx = x + p.width;
		if (width < Mx) Mx = width;
		int My = y + p.height;
		if (height < My) My = height;
		
		int x0; int x1; int y0; int y1; int rowc0; int rowc1;
		for (y0 = 0, y1 = y; y1 < My; y1++) {
			rowc0 = p.width*y0;
			rowc1 = width*y1;
			
			for (x0 = 0, x1 = x; x1 < Mx; x1++) {
				data[rowc1+x1] = data[rowc1+x1] * p.data[rowc0+x0];
				x0++;
			}
			y0++;
		}
	}
	
	/// Calculates the highest and lowest values and in the pattern and linearly scales all cells to fit in the range 0-1.
	void pattern2::fit_values() {
		float min = 1;
		float max = 0;
		
		for (int i = 0; i < width*height; i++) {
			min = fmin(data[i], min);
			max = fmax(data[i], max);
		}
		
		float scale = 1/(max-min);
//		printf("Max: %.2f, Min: %.2f, Scale: %.2f\n", max, min, scale);
		for (int i = 0; i < width*height; i++) {
			data[i] = (data[i] - min) * scale;
		}
	}
	
	/// All values less than min will be set to min, and all values greater than max will be set to max.
	void pattern2::clamp(float min, float max) {
		for (int i = 0; i < width*height; i++) {
			if (data[i] < min) {
				data[i] = min;
			}
			else if (data[i] > max) {
				data[i] = max;
			}
		}
	}
	
	/// Each cell in this pattern gets the max of itself and the corresponding cell in the passed pattern.
	void pattern2::max(pattern2 p) {
		for (int i = 0; i < width*height; i++) {
			if (data[i] < p.data[i]) {
				data[i] = p.data[i];
			}
		}
	}
	
	/// Each cell in this pattern gets the min of itself and the corresponding cell in the passed pattern.
	void pattern2::min(pattern2 p) {
		for (int i = 0; i < width*height; i++) {
			if (data[i] > p.data[i]) {
				data[i] = p.data[i];
			}
		}
	}
	
	pattern2::~pattern2() {
		if (data != NULL) {
			delete[] data;
		}
	}
	
	/* ---- procedural ---- */
	
	procedural::procedural() {}
	
	/// Generates a sin wave emanating from a point.
	pattern2& procedural::sin_circle(pattern2& p, int x, int y, int wavelength, float offset) {
		float xd; float yd; float dis;
		int rowc;
		for (int py = 0; py < p.height; py++) {
			yd = py - y;
			yd *= yd;
			
			rowc = py * p.width;
			for (int px = 0; px < p.width; px++) {
				xd = px - x;
				xd *= xd;
				
				dis = sqrt(xd + yd);
				p.data[px+rowc] = sin(2*3.14159*(dis / wavelength + offset)) / 2 + 0.5;
			}
		}
				
		return p;		
	}
	
	/// Generates a circle with values darkening according to the log10 of distance from the origin.
	pattern2& procedural::log_circle(pattern2& p, int x, int y, int r) {
		float xd; float yd; float dis;
		int rowc;
		for (int py = 0; py < p.height; py++) {
			yd = py - y;
			yd *= yd;
			
			rowc = py * p.width;
			for (int px = 0; px < p.width; px++) {
				xd = px - x;
				xd *= xd;
				
				dis = sqrt(xd + yd);
				p.data[px+rowc] = fmax((log10(r-dis)+1) / (log10(r)+1), 0);
			}
		}
				
		return p;		
	}
	
	/// Generates a circle with values darkening according to the ln of distance from the origin.
	pattern2& procedural::ln_circle(pattern2& p, int x, int y, int r) {
		float xd; float yd; float dis;
		int rowc;
		for (int py = 0; py < p.height; py++) {
			yd = py - y;
			yd *= yd;
			
			rowc = py * p.width;
			for (int px = 0; px < p.width; px++) {
				xd = px - x;
				xd *= xd;
				
				dis = sqrt(xd + yd);
				p.data[px+rowc] = fmax((log(r-dis)+1) / (log(r)+1), 0);
			}
		}
				
		return p;		
	}
	
	/// Generates a circle with values darkening according to the log of distance from the origin.
	pattern2& procedural::lin_circle(pattern2& p, int x, int y, int r) {
		float xd; float yd; float dis;
		int rowc;
		for (int py = 0; py < p.height; py++) {
			yd = py - y;
			yd *= yd;
			
			rowc = py * p.width;
			for (int px = 0; px < p.width; px++) {
				xd = px - x;
				xd *= xd;
				
				dis = sqrt(xd + yd);
				p.data[px+rowc] = fmax(-dis/r+1, 0);
			}
		}
				
		return p;		
	}
	
	pattern2& procedural::logistic_circle(pattern2& p, int x, int y, int r, float s = 5) {
		float xd; float yd; float dis;
		int rowc;
		for (int py = 0; py < p.height; py++) {
			yd = py - y;
			yd *= yd;
			
			rowc = py * p.width;
			for (int px = 0; px < p.width; px++) {
				xd = px - x;
				xd *= xd;
				
				dis = sqrt(xd + yd);
				p.data[px+rowc] = -1 / (1 + pow(2.718282, -s * (dis - r) / r)) + 1;
			}
		}
				
		return p;		
	}
	
	pattern2& procedural::sin_wave(pattern2& p, float dx, float dy, int wavelength, float offset) {
		float m = sqrt(dx*dx + dy*dy);
		dx /= m;
		dy /= m;
		
		int rowc;
		
		for (int py = 0; py < p.height; py++) {
			rowc = py * p.width;
			for (int px = 0; px < p.width; px++) {
				p.data[rowc + px] = sin(2*3.14159*((dx*px + dy*py) / wavelength + offset)) / 2 + 0.5;
			}
		}
		
		return p;
	}
	
	pattern2& procedural::lin_gradient(pattern2& p, float dx, float dy, float start, float end) {
		float m = sqrt(dx*dx + dy*dy);
		dx /= m;
		dy /= m;
		
		float max_dis = sqrt(p.width*p.width + p.height*p.height);
		
		int rowc;
		
		for (int py = 0; py < p.height; py++) {
			rowc = py * p.width;
			for (int px = 0; px < p.width; px++) {
				p.data[rowc + px] = (dx*px + dy*py) / max_dis;
			}
		}
		
		return p;
	}
	
	pattern2& procedural::simplex(pattern2& p, float maxX, float maxY, float minX, float minY) {
		// Working variables
		float s;
		float z;
		
		unsigned int sd = (unsigned int) rng.random_int();
		
		// Check order of min/max
		if (maxX < minX) {
			s = minX;
			minX = maxX;
			maxX = s;
		}
		if (maxY < minY) {
			s = minY;
			minY = maxY;
			maxY = s;
		}
		
		// Variables to store the original specified region.
		float mx = minX;
		float Mx = maxX;
		float my = minY;
		float My = maxY;
		
		// Expand the region provided by the player to include all corners which have any influence over any point in the original region.
		minX--;
		minY--;
		maxX++;
		maxY++;
		
//		printf("Region (%.2f, %.2f) - (%.2f, %.2f) Expanded into (%.2f, %.2f) - (%.2f, %.2f)\n", mx, my, Mx, My, minX, minY, maxX, maxY);
		
		// Perform the inverse equalateralization transform to the upper left and lower right corners of the supplied region.
		s = 0.366025404 * (minX + maxY);
		float high_left_x = minX + s;
		float high_left_y = maxY + s;
		s = 0.366025404 * (maxX + minY);
		float low_right_x = maxX + s;
		float low_right_y = minY + s;
		
		// Perform the transform on the remaining corners as well, although they don't need new variables.
		s = 0.366025404 * (minX + minY);
		minX += s;
		minY += s;
		s = 0.366025404 * (maxX + maxY);
		maxX += s;
		maxY += s;
		
//		printf("Corners become (ABCD): (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)\n", minX, minY, high_left_x, high_left_y, maxX, maxY, low_right_x, low_right_y);
		
		// Cache useful variables.
		int intMinX = (int) ceil(minX);
		int intMaxX = (int) ceil(maxX);
		
		// Divide the newly-defined parallelogram into three segments arranged horizontally, two triangles and one parallelogram in the middle.
		
		// In cases where the sampled region has a low enough aspect ratio, the high_left_x might be farther right than the low_right_x value.
		// In this case we must ensure the regions are re-ordered correctly.
		float first_switch;
		float last_switch;
		if (high_left_x < low_right_x) {
			first_switch = high_left_x;
			last_switch = low_right_x;
		} else {
//			printf("Swapping switch points.\n");
			first_switch = low_right_x;
			last_switch = high_left_x;
		}
		
//		printf("Switches at %.2f & %.2f\n", first_switch, last_switch);
			
		// Assign one of four random vectors to each lattice point (point having integer coordinates) contained in the parallelogram.
		// First Iterate over integer x values from the left-most point in the parallelogram to the right-most point.
		// For each x, iterate over all y values such that (x, y) is a point in the parallelogram.
		
		// buffer2 contains the randomly-chosen vector for all lattice points with influence over the supplied region.
		
		// Important: For some n, buffer1[n] gives the y value of the lattice point whose assigned vector is given at buffer2[n][0].
		// The y-value of the lattice point whose vector is given at buffer[n][a] is one greater than the y-value for buffer[n][a-1]
		
		s = 0.267949192f;
		z = 3.732050808f;
		
		// Allocate space for a jagged matrix.
		int num_cols = intMaxX - intMinX;
		unsigned char** buffer2 = new unsigned char*[num_cols];
		int*   buffer1 = new int[num_cols];
		
//		printf("Allocating for %d columns in range %.2f - %.2f\n", num_cols, minX, maxX);
		
		uint64_t col_seed;
		uint64_t pix_seed;
		int I;
		int min_y;
		int max_y;
		for (int x = intMinX; x < maxX; x++) {
//			printf("Column %d\n", x);
			I = x - intMinX;
			col_seed = x ^ sd;
			col_seed <<= 32;
			
			if (x < first_switch) {
				// Allocate space for this row.
				min_y = ceil((x - minX) * s + minY);
				max_y = floor((x - minX) * z + minY);
				
//				printf("buffer2[%d] gets %d - %d + 1.\n", I, max_y, min_y);
				
				buffer2[I] = new unsigned char[max_y - min_y + 1];
				buffer1[I] = min_y;
				
				// Iterate over y values.
				for (int y = min_y; y <= max_y; y++) {
//					printf("Row 0 / %d\n", y);
					unsigned int a = y ^ sd;
					pix_seed = col_seed | y;
					rng.init(hashing::FNV_32(pix_seed));
					buffer2[I][y-min_y] = abs(rng.random_int() % 4);
				}
			}
			else if (x < last_switch) {
				// Allocate space for this row.
				min_y = ceil((x - minX) * s + minY);
				max_y = floor((x - maxX) * s + maxY);
				
//				printf("buffer2[%d] gets %d - %d + 1.\n", I, max_y, min_y);
				
				buffer2[I] = new unsigned char[max_y - min_y + 1];
				buffer1[I] = min_y;
				
				// Iterate over y values.
				for (int y = min_y; y <= max_y; y++) {
//					printf("Row 1 / %d\n", y);
					pix_seed = col_seed | y;
					rng.init(hashing::FNV_32(pix_seed));
					buffer2[I][y-min_y] = abs(rng.random_int() % 4);
				}
			}
			else {
				// Allocate space for this row.
				min_y = ceil((x - maxX) * z + maxY);
				max_y = floor((x - maxX) * s + maxY);
				
//				printf("buffer2[%d] gets %d - %d + 1.\n", I, max_y, min_y);
				
				buffer2[I] = new unsigned char[max_y - min_y + 1];
				buffer1[I] = min_y;
				
				// Iterate over y values.
				for (int y = min_y; y <= max_y; y++) {
//					printf("Row 2 / %d\n", y);
					pix_seed = col_seed | y;
					rng.init(hashing::FNV_32(pix_seed));
					buffer2[I][y-min_y] = abs(rng.random_int() % 4);
				}
			}
		}
		
//		printf("Vector Assignment Complete.\n");
		
		// Now buffer2 contains a random vector for every relevant lattice point.
		// Now we iterate over every point in the supplied region to calculate the simplex noise at each point.
		// Store the 3corners of the simplex that contains point p and their values.
		vec2<float> px; vec2<float> py; vec2<float> pz;
		vec2<float> vx; vec2<float> vy; vec2<float> vz;
		
		// Ugh
		float left; float low; float right; float high;
		float u; float v; float w; float m;
		float X; float Y; float Px; float Py;
		vec2<float> Uvec; vec2<float> Vvec; vec2<float> Wvec;
		for (int x = 0; x < p.width; x++) {
			for (int y = 0; y < p.height; y++) {
				// Get input point coordinates
				Px = ((float) x / p.width) * (Mx - mx) + mx;
				Py = ((float) y / p.height) * (My - my) + my;
				
				// Apply the equalateralization transform to the input point
				s = 0.3660254037f * (Px + Py);
				X = Px + s;
				Y = Py + s;
				
//				printf("\n(%d, %d) -> (%.2f, %.2f) -> (%.2f, %.2f)\n", x, y, Px, Py, X, Y);
				
				// Get the corners of the square in which (X, Y) resides.
				left = floor(X);
				low = floor(Y);
				right = floor(X+1);
				high = floor(Y+1);
				
//				printf("Bounded by %.2f < x < %.2f & %.2f < y < %.2f.\n", left, right, low, high);
				
				// In quadrants 2 and 4, due to one value being negative, either (X % 1) is always greater than (Y % 1) or vice verse. This code corrects that by making negatives positve.
				if (X < 0) {
					X = fmodf(X, 1) + 1;
				}
				if (Y < 0) {
					Y = fmodf(Y, 1) + 1;
				}
				
				// Get the two corners that the point must belong to.
				px = vec2<float>(left, low);
				py = vec2<float>(right, high);
				// Get the last corner.
				if (fmodf(X, 1) > fmodf(Y, 1)) {
					pz = vec2<float>(right, low);
				} else {
					pz = vec2<float>(left, high);
				}
				
//				printf("Bounding half-square is: (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)\n", px.x, px.y, py.x, py.y, pz.x, pz.y);
				
				// Get the random vectors stored in buffer2
				// Convert (x, y) coords of each point to (u, v) buffer2 coordinates.
				u = px.x - intMinX;
				v = px.y - (float) buffer1[(int) u];
//				printf("px -> uv: (%.2f, %.2f), (%.2f, %.2f)\n", px.x, px.y, u, v);
				vx = vecpick2[buffer2[(int) u][(int) v]];
				u = py.x - intMinX;
				v = py.y - (float) buffer1[(int) u];
//				printf("py -> uv: (%.2f, %.2f), (%.2f, %.2f)\n", py.x, py.y, u, v);
				vy = vecpick2[buffer2[(int) u][(int) v]];
				u = pz.x - intMinX;
				v = pz.y - (float) buffer1[(int) u];
//				printf("pz -> uv: (%.2f, %.2f), (%.2f, %.2f)\n", pz.x, pz.y, u, v);
				vz = vecpick2[buffer2[(int) u][(int) v]];
				
				// Skew the corners of this simplex into a simplex grid.
				s = 0.2113248654f * (px.x + px.y);
				px = vec2<float>(px.x - s, px.y - s);
				
				s = 0.2113248654f * (py.x + py.y);
				py = vec2<float>(py.x - s, py.y - s);
				
				s = 0.2113248654f * (pz.x + pz.y);
				pz = vec2<float>(pz.x - s, pz.y - s);
				
//				printf("Bounding simplex is: (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)\n", px.x, px.y, py.x, py.y, pz.x, pz.y);
				
				Uvec = vec2<float>(Px - px.x, Py - px.y);
				Vvec = vec2<float>(Px - py.x, Py - py.y);
				Wvec = vec2<float>(Px - pz.x, Py - pz.y);
				
				// Calculate influence of each corner to the given point by distance.
				u = 2 * fmin(Uvec.sqr_mag(), 0.5);
				v = 2 * fmin(Vvec.sqr_mag(), 0.5);
				w = 2 * fmin(Wvec.sqr_mag(), 0.5);
				
//				printf("Corner-Distance vectors are (%.2f, %.2f) @ %.2f, (%.2f, %.2f) @ %.2f, (%.2f, %.2f) @ %.2f\n", Uvec.x, Uvec.y, u, Vvec.x, Vvec.y, v, Wvec.x, Wvec.y, w);
				
				// Modify values to simulate a quadratice falloff of each corner's influence
				u = u * (u - 1) - u + 1;
				v = v * (v - 1) - v + 1;
				w = w * (w - 1) - w + 1;
				
				// Normalize u, v, and w so they sum to 1
				m = u + v + w;
				u = u / m; v = v / m; w = w / m;
				
//				printf("Corner-Distance vectors are (%.2f, %.2f) @ %.2f, (%.2f, %.2f) @ %.2f, (%.2f, %.2f) @ %.2f\n", Uvec.x, Uvec.y, u, Vvec.x, Vvec.y, v, Wvec.x, Wvec.y, w);
//				printf("Randomly Assigned vectors are (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)\n", vx.x, vx.y, vy.x, vy.y, vz.x, vz.y);
				
				// Get the dot product of the vector pointing from each corner toward the point, and the corner's randomly assigned vector. Then multiply that contribution by this point's influence.
				u *= vec2<float>::dot(Uvec, vx);
				v *= vec2<float>::dot(Vvec, vy);
				w *= vec2<float>::dot(Wvec, vz);
				
				p.data[x + y*p.width] = (u + v + w + 1) / 2;
				
//				printf("Final weights are %.2f, %.2f, %.2f for a value of %f\n", u, v, w, p.data[x+y*p.width]);
			}
		}
		
		delete[] buffer1;
		for (int i = 0; i < num_cols; i++) {
			delete[] buffer2[i];
		}
		delete[] buffer2;
		
		return p;
	}
	
	pattern2& procedural::worley(pattern2& p, float maxX, float maxY, float minX, float minY) {
		unsigned int sd = rng.random_int();
		
		// Ensure the min/max values are in the right order
		float s;
		if (minX > maxX) {
			s = minX;
			minX = maxX;
			maxX = s;
		}
		if (minY > maxY) {
			s = minY;
			minY = maxY;
			maxY = s;
		}

		// Store original specified region
		float mx = minX;
		float Mx = maxX;
		float my = minY;
		float My = maxY;

		// Adjust region outward
		minX = floor(minX) - 1;
		maxX = ceil(maxX) + 1;
		minY = floor(minY) - 1;
		maxY = ceil(maxY) + 1;
		
		// Populate a 2D buffer with a random Vector between (0, 0) and (1, 1) for each square in the region.
		int vec_w = (int) (maxX - minX);
		int vec_h = (int) (maxY - minY);
		vec2<float>* pb = new vec2<float>[ vec_w*vec_h ];
		vec2<float>* pbr;
		
		uint64_t row_seed;
		int ix; int iy;
		for (int y = (int) minX; y < My; y++) {
			row_seed = y ^ sd;
			row_seed <<= 32;
			
			iy = (int) (y - minY);
			
			pbr = pb + iy*vec_w;
			for (int x = (int) minX; x < Mx; x++) {
				rng.init(hashing::FNV_32(row_seed | (x ^ sd)));
				
				ix = (int) (x - minX);
				
				pbr[ix] = vec2<float>(rng.random_val(), rng.random_val());
				
//				printf("Assigned (%.2f, %.2f) to (%d, %d)\n", pbr[ix].x, pbr[ix].y, x, y);
			}	
		}
		
		float X; float Y;
		float A; float B;
		float m;
		float searchMinX; float searchMinY; float searchMaxX; float searchMaxY;
		
		float tempVecX; float tempVecY;
		
		for (int y = 0; y < p.height; y++) {
			for (int x = 0; x < p.width; x++) {
				// Calculate position of this point in worley-space
				X = (float) x / p.width  * (Mx - mx) + mx;
				Y = (float) y / p.height * (My - my) + my;
				
//				printf("(%d, %d) -> (%.2f, %.2f) -> ", x, y, X, Y);
				
				// Get coordinates of upper right and lower left grid squares to search.
				searchMinX = floor(X) - 1;
				searchMinY = floor(Y) - 1;
				searchMaxX = searchMinX + 3;
				searchMaxY = searchMinY + 3;
				
				// Modify X and Y to be in terms of the 3x3 grid square space;
				X -= searchMinX;
				Y -= searchMinY;
				
//				printf("(%.2f, %.2f) searches (%.1f, %.1f) - (%.1f, %.1f)\n", X, Y, searchMinX, searchMinY, searchMaxX, searchMaxY);
				
				s = 2;
				// Iterate over 9 relevant points to find which is the closest to the current point.
				for (int b = searchMinY; b < searchMaxY; b++) {
					pbr = pb + (b - (int) minY)*vec_w;
					for (int a = searchMinX; a < searchMaxX; a++) {
						A = a - searchMinX;
						B = b - searchMinY;
						
						tempVecX = pbr[a - (int) minX].x + A - X;
						tempVecY = pbr[a - (int) minX].y + B - Y;
						
						m = tempVecX * tempVecX + tempVecY * tempVecY;
						
						if (m < s) {
							s = m;
						}
					}
				}
				
				// Now s should contain the square distance from this point to the nearest point.
				p.data[x+y*p.width] = sqrt(s) / 1.41;
			}
		}
		
		delete[] pb;
		
		return p;
	}
	
	pattern2& procedural::band(pattern2& p, float inc) {
		for (int i = 0; i < p.width*p.height; i++) {
			p.data[i] = round(p.data[i] / inc) * inc;
		}
		
		return p;
	}
}

