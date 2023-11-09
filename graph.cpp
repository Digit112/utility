#include <cmath>

namespace util {
	/* ---- linear ---- */
	
	float linear::derivative() const {
		return a;
	}
	
	quadratic linear::integrate(float C) const {
		return quadratic(a/2, b, C);
	}
	
	float linear::evaluate(float x) const {
		return a*x + b;
	}
	
	/* ---- quadratic ---- */
	
	linear quadratic::derivative() const {
		return linear(2*a, b);
	}
	
	cubic quadratic::integrate(float C) const {
		return cubic(a/3, b/2, c, C);
	}
	
	float quadratic::evaluate(float x) const {
		return a*x*x + b*c + c;
	}
	
	/* ---- cubic ---- */
	
	quadratic cubic::derivative() const {
		return quadratic(3*a, 2*b, c);
	}
	
	float cubic::evaluate(float x) const {
			return a*x*x*x + b*x*x + c*x + d;
	}
	
	/* ---- cubic_interpolator ---- */
	
	void swap_rows(float** mat, int i, int j) {
		float* temp = mat[i];
		mat[i] = mat[j];
		mat[j] = temp;
	}
	
	bool cubic_interpolator::interpolate(const int num_points, vec2<float>* p) {
		int N = 4*num_points - 4;
		
		// mat[row][column], column = N indexes the RHS.
		float** mat = new float*[N];
		
		for (int i = 0; i < N; i++) {
			mat[i] = new float[N+1];
			
			for (int j = 0; j <= N; j++) {
				mat[i][j] = 0;
			}
		}
		
		// Cache squares and cubes of x values.
		// New is used to avoid CUDA errors.
		float* squares = new float[num_points];
		float* cubes = new float[num_points];
		for (int i = 0; i < num_points; i++) {
			squares[i] = p[i].x * p[i].x;
			cubes[i] = squares[i] * p[i].x;
		}
		
		// Load matrix
		int r = 0;
		
		// Restrict functions by a pair of points that they must pass through.
		for (int i = 0; i < num_points-1; i++) {
			// a_i * x_i^3 + b_i * x_i^2 + c_i * x_i + d_i = y_i
			mat[r][i*4  ] = cubes[i];
			mat[r][i*4+1] = squares[i];
			mat[r][i*4+2] = p[i].x;
			mat[r][i*4+3] = 1;
			mat[r][N] = p[i].y;
			
			r++;
			
			// a_i * x_(i+1)^3 + b_i * x_(i+1)^2 + c_i * x_(i+1) + d_i = y_(i+1)
			mat[r][i*4  ] = cubes[i+1];
			mat[r][i*4+1] = squares[i+1];
			mat[r][i*4+2] = p[i+1].x;
			mat[r][i*4+3] = 1;
			mat[r][N] = p[i+1].y;
			
			r++;
		}

		// Restrict adjacent segments to have the same first derivative where they meet.
		for (int i = 0; i < num_points-2; i++) {
			// 3 * a_i * x_(i+1)^2 + 2 * b_i * x_(i+1) + c_i  -  3 * a_(i+1) * x_(i+1)^2 - 2 * b_(i+1) * x_(i+1) - c_(i+1) = 0
			mat[r][i*4  ] = 3 * squares[i+1];
			mat[r][i*4+1] = 2 * p[i+1].x;
			mat[r][i*4+2] = 1;
			
			mat[r][(i+1)*4  ] = -3 * squares[i+1];
			mat[r][(i+1)*4+1] = -2 * p[i+1].x;
			mat[r][(i+1)*4+2] = -1;
			
			r++;
		}

		// Restrict adjacent segments to have the same second derivative where they meet.
		for (int i = 0; i < num_points-2; i++) {
			// 6 * a_i * x_(i+1) + 2 * b_i  -  6 * a_(i+1) * x_(i+1) - 2 * b_(i+1) = 0;
			mat[r][i*4  ] = 6 * p[i+1].x;
			mat[r][i*4+1] = 2;
			
			mat[r][(i+1)*4  ] = -6 * p[i+1].x;
			mat[r][(i+1)*4+1] = -2;
			
			r++;
		}

		// Restrict the second derivative at the first and last points.
		// 6 * a_1 * x_1 + 2 * b_1 = 0
		mat[r][0] = 6 * p[0].x;
		mat[r][1] = 2;

		r++;

		// 6 * a_(n-1) * x_n + 2 * b_(n-1) = 0
		mat[r][(num_points-2)*4  ] = 6 * p[num_points-1].x;
		mat[r][(num_points-2)*4+1] = 2;
		
		// Perform gaussian elimination to bring the matrix into row echelon form.
		// The matrix is not put into reduced row echelon form.
		for (int k = 0; k < N; k++) {
			float max_i = fabs(mat[k][k]);
			int max_i_row = k;
			
			for (int i = k+1; i < N; i++) {
				if (fabs(mat[i][k]) > max_i) {
					max_i = fabs(mat[i][k]);
					max_i_row = i;
				}
			}
			
			// If the largest entry is 0, there is no solution.
			if (max_i == 0) {
				for (int i = 0; i < N; i++) delete[] mat[i];
				delete[] mat;
				delete[] squares;
				delete[] cubes;
				
				return false;
			}
			
			if (max_i_row != k) {
				swap_rows(mat, k, max_i_row);
			}
		
			// Add multiples of the kth row to each of the below columns in order to make all of the entries beneath k 0.
			for (int i = k+1; i < N; i++) {
				double m = -mat[i][k] / mat[k][k];
				
				for (int j = 0; j <= N; j++) {
					mat[i][j] += m * mat[k][j];
				}
			}
		}
		
		// Solve for the unknowns in reverse order. The results are placed in column N in the RHS.
		// Solves from bottom to top
		for (int i = N-1; i >= 0; i--) {
			// Subtract all previous terms.
			for (int j = N-1; j > i; j--) {
				mat[i][N] -= mat[j][N] * mat[i][j];
			}
			
			mat[i][N] /= mat[i][i];
		}
		
		// Reallocate the segments to the appropriate size.
		if (segments != nullptr) {
			delete[] segments;
		}
		
		segments = new cubic[num_points - 1];
		
		for (int i = 0; i < num_points - 1; i++) {
			segments[i] = cubic(
				mat[i*4  ][N],
				mat[i*4+1][N],
				mat[i*4+2][N],
				mat[i*4+3][N]
			);
		}
		
		for (int i = 0; i < N; i++) delete[] mat[i];
		delete[] mat;
		delete[] squares;
		delete[] cubes;
		
		return true;
	}
	
	cubic_interpolator::~cubic_interpolator() {
		if (segments != nullptr) {
			delete[] segments;
		}
	}
}