namespace util {
	/* ---- expr ---- */
	
	/// Creates a constant using the no-arg constructor of T.
	template<class T> expr<T>::expr() : children(nullptr), num_children(0), v(T()) {}
	
	/// Creates a constant with the passed value. Calls T's copy constructor.
	template<class T> expr<T>::expr(T val) : children(nullptr), num_children(0), v(val) {}
	
	/// Creates an operation using the passed function and children. Default operations are defined below, which can be passed as the first parameter to this constructor.
	template<class T> expr<T>::expr(T (*oper)(T* o, int n), int num_operands, expr<T>* operands) : children(nullptr), num_children(num_operands), v(oper) {
		// Allocate space for children and copy arguments into them.
		children = operands;
	}
	
	/// Evaluate this node. If this node is an operation, recursively evaluate all children.
	template<class T> T expr<T>::evaluate(int depth) {
		for (int j = 0; j < depth; j++) printf("  ");
		printf("Evaluating: w/ %d children.\n", num_children);
		if (num_children == 0) {
			// Base case. Return raw value.
			for (int j = 0; j < depth; j++) printf("  ");
			printf("Returning Constant %.2f...\n", v.v);
			return v.v;
		}
		else {
			// Recursive case. Evaluate all children and then this node.
			for (int j = 0; j < depth; j++) printf("  ");
			T results[num_children];
			for (int i = 0; i < num_children; i++) {
				for (int j = 0; j < depth; j++) printf("  ");
				printf("Child %d:\n", i);
				
				results[i] = children[i].evaluate(depth+1);
			}
			T result = v.o(results, num_children);
			for (int j = 0; j < depth; j++) printf("  ");
			printf("Returning Evaluated %.2f...\n", result);
			return result;
		}
	}
}











