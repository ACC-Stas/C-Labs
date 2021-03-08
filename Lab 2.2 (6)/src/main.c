#include <stdio.h>
#include <math.h>
#include "src.h"

int main() {
	printf("Enter epsilon: ");
	double eps;
	eps = getDouble(0.0000000001, 10000000);
	printf("Enter andgle in radians from 0 to Pi/2: "); /*sin is periodic function*/
	double angle;
	angle = getDouble(0,1.5708);
	int n;
	n = sinDecomposion(angle, sin(angle), eps);
	printf("%d decomposion elements are requered for this accuracy", n);
	return 0;
}