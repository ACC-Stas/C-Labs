#include "src.h"
#include <math.h>
#include <assert.h>

void testSinDecomposion() {
	double eps, angle;
	eps = 0.0000000001;
	angle = 0.753;
	assert(sinDecomposion(angle, sin(angle), eps) == 6);
	eps = 0.0000000001;
	angle = 0.00789;
	assert(sinDecomposion(angle, sin(angle), eps) == 2);
	eps = 0.001;
	angle = 0.01;
	assert(sinDecomposion(angle, sin(angle), eps) == 1);
}

int main() {
	testSinDecomposion();
	return 0;
}