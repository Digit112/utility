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