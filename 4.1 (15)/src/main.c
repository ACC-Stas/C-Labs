#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "src.h"


int main() {
	printf("Enter number of lines you want to work with: ");
	int numberOfLines = getInt(1,50);
	printf("Enter maximum length of line you want to work with: ");
	int lineLengths = getInt(2,140);
	lineLengths++;
	char* str = (char*)malloc(lineLengths*sizeof(char));
	if (str == NULL) {
		printf("Can't allocate memory\n");
		return 1;
	}
	int i;
	for (i = 0; i < numberOfLines; i++) {
		if (gets(str) == NULL) {
			printf("Can't get line\n");
			continue;
		}
		str[lineLengths - 1] = '\0'; /*for the case of too long input*/
		printf("Input line: %s\n", str);
		swapLetters(str);
		printf("changed words: %s\n", str);
		deleteExcessLetters(str);
		printf("delete excess letters: %s\n", str);
	}
	printf("Enter anything to end: ");
	getchar();
	free(str);
	return 0;
}