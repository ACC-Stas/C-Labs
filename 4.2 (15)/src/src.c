#include <stdio.h>
#include "src.h"

void searchWords(FILE* words, char** dictionary, int dictionSize, int* output) { 
	char wordLine[556];
	while (fgets(wordLine, 554, words) != NULL) {
		int i,j,g, isword;
		for (i = 0; i < dictionSize; i++) {
			for (j = 0; wordLine[j] != '\0'; j++) {
				if ((wordLine[j] >= 'A' && wordLine[j] <= 'Z') || (wordLine[j] >= 'a' && wordLine[j] <= 'z')) {
					isword = 1;
					g = 0;
					while ((dictionary[i][g] >= 'A' && dictionary[i][g] <= 'Z') || (dictionary[i][g] >= 'a' && dictionary[i][g] <= 'z')) {
						if (dictionary[i][g] != wordLine[j]) {
							isword = 0;
						}
						g++;
						j++;
					}
					if (isword) {
						output[i]++;
					}
				}
			}
		}
	}
}