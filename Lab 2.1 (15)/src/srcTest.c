#include "src.h"
#include <assert.h>

void testCalculateLength() {
	assert(calculateLength(8, 3, 2021, 15, 2, 2022) == 344);
	assert(calculateLength(8, 3, 2021, 9, 3, 2021) == 1);
}
void testGetProgrammersCost() {
	assert(getProgrammersCost(156260, 100, 1000) == 125008000000);
}

int main() {
	testCalculateLength();
	testGetProgrammersCost();
	return 0;
}