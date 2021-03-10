#include "main.h"
#include <assert.h>

void testMaxFibonachi() {
	assert(46 == maxFibonachi());
}

void testMaxSumFibonachi() {
	assert(1836311902 == maxSumFibonachi());
}

#undef main
int main() {
	testMaxFibonachi();
	testMaxSumFibonachi();
	return 0;
}