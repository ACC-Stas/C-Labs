#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "src.h"

void testSearchWords() {
	const char* Dictionary_FILENAME = "dictionary.txt";
	FILE* dictionary = fopen("dictionary.txt", "r");
	if (dictionary == NULL) {
		printf("Can't access dictionary\n");
		exit(1);
	}
	int numberOfDictionaryWords;
	if (fscanf(dictionary, "%d", &numberOfDictionaryWords) != 1) {
		printf("Can't read number of lines in dictionary\n");
		exit(1);
	}
	getc(dictionary); /*enter after number*/
	char** dictionaryWords = (char**)malloc(numberOfDictionaryWords * sizeof(char*));
	if (dictionaryWords == NULL) {
		printf("Can't allocate memory\n");
		exit(1);
	}
	int i;
	for (i = 0; i < numberOfDictionaryWords; i++) {
		dictionaryWords[i] = (char*)malloc(256 * sizeof(char)); /*can't be bigger than 256*/
		if (dictionaryWords[i] == NULL) {
			printf("Can't allocate memory\n");
			i--;
			for (; i >= 0; i--) {
				free(dictionaryWords[i]);
			}
			free(dictionaryWords);
		}
		fgets(dictionaryWords[i], 255, dictionary);
		dictionaryWords[i][255] = '\0';
	}
	fclose(dictionary);
	int* dictionaryWordsCounter = (int*)malloc(numberOfDictionaryWords * sizeof(int));
	for (i = 0; i < numberOfDictionaryWords; i++) {
		dictionaryWordsCounter[i] = 0;
	}
	char nameOfFile[] = "text.txt";
	FILE* textFile = fopen(nameOfFile, "r");
	if (textFile == NULL) {
		printf("Can't open txt file\n");
		exit(1);
	}
	searchWords(textFile, dictionaryWords, numberOfDictionaryWords, dictionaryWordsCounter);
	fclose(textFile);
	int requiredOutput[6];
	requiredOutput[0] = 0;
	requiredOutput[1] = 2;
	requiredOutput[2] = 1;
	requiredOutput[3] = 2;
	requiredOutput[4] = 1;
	requiredOutput[5] = 1;
	for (i = 0; i < 6; i++) {
		assert(dictionaryWordsCounter[i] == requiredOutput[i]);
	}
	for (i = 0; i < numberOfDictionaryWords; i++) {
		free(dictionaryWords[i]);
	}
	free(dictionaryWords);
}

int main() {
	testSearchWords();
	return 0;
}