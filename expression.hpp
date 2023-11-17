#ifndef UTIL_EXPRESSION
#define UTIL_EXPRESSION

#include <cmath>
#include <cstdarg>

namespace util {
	using namespace std;
	
	/// The expr ("expression") class is an expression tree node. By combining them, an expression tree can be created.
	/** The evaluate function can be used to get a result.
	*   If this is a leaf node, value is of type T. Otherwise, it is an operation represented by a function pointer.
	*   Many default functions are defined for convenience, in all-caps. */
	template<class T> class expr {
	private:
		// Either a value of type T or an operation on parameters of type T.
		union value {
			T v;
			T (*o)(T*, int); // Takes a list of operands and the number of operands.
			
			value(T v) : v(v) {}
			value(T (*o)(T*, int)) : o(o) {}
		};
	
	public:
		// Nodes that are children of this node.
		expr<T>* children;
		int num_children;
		
		// Value or Operation.
		value v;
		
		expr();
		expr(T value);
		expr(T (*oper)(T*, int), int num_operands, expr<T>* operands);
		
		T evaluate(int depth=0);
		
		// Default functions for convenience.
		// Arithmetic
		static T ADD(T* o, int n) {return o[0] + o[1];}
		static T SUB(T* o, int n) {return o[0] - o[1];}
		static T MUL(T* o, int n) {return o[0] * o[1];}
		static T DIV(T* o, int n) {return o[0] / o[1];}
		static T POW(T* o, int n) {return pow((double) o[0], (double) o[1]);}
		static T NEG(T* o, int n) {return -o[0];}
		
		// Comparison
		static T GT (T* o, int n) {return o[0] > o[1];}
		static T LT (T* o, int n) {return o[0] < o[1];}
		static T GTE(T* o, int n) {return o[0] >= o[1];}
		static T LTE(T* o, int n) {return o[0] <= o[1];}
		static T EQ (T* o, int n) {return o[0] == o[1];}
		static T NEQ(T* o, int n) {return o[0] != o[1];}
		
		static T MAX(T* o, int n) {return o[0] > o[1] ? o[0] : o[1];}
		static T MIN(T* o, int n) {return o[0] < o[1] ? o[0] : o[1];}
		
		// Boolean
		static T AND(T* o, int n) {return o[0] && o[1];}
		static T OR (T* o, int n) {return o[0] || o[1];}
		static T NOT(T* o, int n) {return !o[0];}
		
		// Bitwise
		static T BWA(T* o, int n) {return o[0] & o[1];}
		static T BWO(T* o, int n) {return o[0] | o[1];}
		static T XOR(T* o, int n) {return o[0] ^ o[1];}
		static T INV(T* o, int n) {return ~o[0];}
		
		// Array
		static T AVG(T* o, int n) {
			float avg = o[0];
			for (int i = 1; i < n; i++) {
				avg += o[i];
			}
		}
	};
}

#include "expression.cpp"

#endif
