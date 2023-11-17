/** \mainpage
A collection of utilities that solve issues I find myself encountering frequently.

Include util.hpp to include the entire library.

\section Vector

This section includes the vec2, vec3, & vec4 classes for representing 2, 3, & 4 dimensional vectors respectively. It also includes the complex class, deriving from vec2, and the quaternion class, deriving from vec4. These are useful for representing rotations in 2 and 3 dimensions, respectively. These include a template parameter for the underlying type which is expected but not required to be a scalar type. Implicit conversions between these classes and their variants with different template parameters are generally defined.

When compiling for the GPU with the Nvidia compiler ("nvcc"), the classes and members of the vector library will be accessible in device code.

\section Procedural

This library includes utilities for procedural generation. It also includes utilities for random number generation and hash functions. Currently, only the following algorithms are implemented, with suppot for more likely coming in the future:

Hashing:
- FNV32

RNG:
- xoshiro128**

All hash functions are provided by the util::hashing class. Each RNG, however, has its own class.

The util::pattern2 class represents a sequence of values and defines operations between them. The util::procedural class itself provides the generating functions, including sin waves, gradients, and so on. The most complex patterns are simplex noise and worley noise. 3D variants will hopefully be implemented in the future.

\section Expression

The expression class allows the construction of expression trees. Each expression node represents a function that operates on a number of arguments which may not be fixed, and produces a single value. The type of the arguments and the rturn type are both specified by the template parameter. 

*/

#ifdef USE_GPU
	#include "vec_GPU.hpp"
#else
	#include "vec.hpp"
#endif

#include "procedural.hpp"
#include "geometry.hpp"
#include "expression.hpp"
#include "color.hpp"
#include "graph.hpp"

#ifdef UTIL_LEGACY_VECTORS
namespace util {
	typedef vec2<double> vecd2;
	typedef vec3<double> vecd3;
	typedef vec4<double> vecd4;

	typedef vec2<int> veci2;
	typedef vec3<int> veci3;
	typedef vec4<int> veci4;
}
#endif