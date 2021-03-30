#include <assert.h>
#include <stdlib.h>
#include "src.h"

void testSwapLetters() {
	char* str = (char*)malloc(15 * sizeof(char));
	str[14] = '\0';
	str[0] = ' ';
	str[1] = 'a';
	str[2] = 's';
	str[3] = 'd';
	str[4] = 'f';
	str[5] = ' ';
	str[6] = 'd';
	str[7] = 's';
	str[8] = 'd';
	str[9] = 'f';
	str[10] = ' ';
	str[11] = 's';
	str[12] = 's';
	str[13] = 's';
	swapLetters(str);
	char answers[] = " fsda fsdd sss";
	int i;
	for (i = 0; i < 14; i++) {
		assert(str[i] == answers[i]);
	}
}

void testDeleteExcessLetters() {
	char* str = (char*)malloc(15 * sizeof(char));
	str[14] = '\0';
	str[0] = ' ';
	str[1] = 'a';
	str[2] = 's';
	str[3] = 'd';
	str[4] = 'f';
	str[5] = ' ';
	str[6] = 'd';
	str[7] = 's';
	str[8] = 'd';
	str[9] = 'f';
	str[10] = ' ';
	str[11] = 's';
	str[12] = 's';
	str[13] = 's';
	deleteExcessLetters(str);
	char answers[] = " asdf dsf  s  ";
	int i;
	for (i = 0; i < 14; i++) {
		assert(str[i] == answers[i]);
	}
}

int main() {
	testSwapLetters();
	testDeleteExcessLetters();
	return 0;
}