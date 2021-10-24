# utility
A collection of some C++ tools I made. After copying the tools around and finding multiple incompatible copies of it in different projects, I thought that it's time to standardize.

Includes:
procedural - Classes and functions for procedural generation, including PRNG implementations, Hash functions, Simplex & Worley Noise, and maze generation.
vec - 2, 3, and 4 dimensional vectors with double-precision floating point and integer variants. Also includes Quaternion and Complex classes.

## Quick Documentation
### vec
Includes 1, 2, 3, and 4 dimesional vector classes. For each dimension, there are two variants, one where the elements are integers and another where the elements are doubles.

Each class is named "vec" with an appended 'd' for double or 'i' for int, and an appended number for the dimension. The smallest is the 2-dimensional integer vector veci2 and the largest is the 4-dimension double vector vecd4.

All arithmetic operations are defined for each class as being applied component-wise. That is, vector addition and subtraction work as expected, vector multiplication and division work by applying scalar multiplication or division to the corresponding components of each vector. For the dot and cross products, static dot() and cross() functions are provided. The cross product is only defined for 3-dimensionaal vectors. for all vectors, there is a normalize() method for normalizing the vector to a magnitude of 1, and a normalize(*n*) method for normalizing the vector to a magnitude of *n*. All normalize functions return a vector with double-precision floating-point components. For all vectors, there is also a mag() and sqr_mag() function. For 2D vectors, there is an arg() function whose range is \[-pi, pi).

The library also contains "complex" and "quaternion" classes, deriving directly from vecd2 and vecd4, respectively. For these classes, the multiplication and division operators are redefined based on the algebraic notions of multiplication and division for these kinds of numbers. In order to scale them, a static scale() function is available. Both classes overload the unary '~' operator to return the complex conjugate, which is the same number but with the imaginary component(s) negated.

### procedural
Includes class specifically designed for the storage and manipulation of 2D matrices of double-precision floating point values, instances of which are used to hold the results of various utility functions capable of generating everything from simple checkerboard and sine wave patterns to simplex and worley noise. The library is still very limited, but will eventually contain many PRNG and hash functions as well as many random-number generating utilities (Random vector on unit circle, random sample from normal distribution, etc.) As of right now, only the xoshiro PRNG and FNV_32 hash function are available in those categories.