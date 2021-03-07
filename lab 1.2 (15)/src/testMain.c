#include "main.h"
#include <assert.h>

void testMaxFibonachi() {
	int requiredNumber = 46;
	assert(requiredNumber == maxFibonachi());
}

void testMaxSumFibonachi() {
	int requiredNumber = 1836311902;
	assert(requiredNumber == maxSumFibonachi());
}

#undef main
int main() {
	testMaxFibonachi();
	testMaxSumFibonachi();
	return 0;
}