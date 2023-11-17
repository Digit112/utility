#include <cstdio>
#include <cstdint>

#include "utility/util.hpp"

using namespace util;

int main() {
	{
		expr<float> n[] = {3, 7};
		expr<float> o[] = {6, {expr<float>::ADD, 2, n}};
		expr<float> a(expr<float>::MUL, 2, o);
		printf("%f\n", a.evaluate()); // Should print 60, the result of 6*(3+7)
	}
	
	printf("Done.\n");
	return 0;
}