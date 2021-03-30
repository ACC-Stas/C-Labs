#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "src.h"

int main() {
	const char* Dictionary_FILENAME = "dictionary.txt";
	FILE* dictionary = fopen("dictionary.txt", "r");
	if (dictionary == NULL) {
		printf("Can't access dictionary\n");
		return 1;
	}
	int numberOfDictionaryWords; 
	if (fscanf(dictionary, "%d", &numberOfDictionaryWords) != 1) {
		printf("Can't read number of lines in dictionary\n");
		return 1;
	}
	getc(dictionary); /*enter after number*/
	char** dictionaryWords = (char**)malloc(numberOfDictionaryWords * sizeof(char*));
	if (dictionaryWords == NULL) {
		printf("Can't allocate memory\n");
		return 1;
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
	printf("Enter name of txt file whit .txt on the end: ");
	char nameOfFile[100];
	gets(nameOfFile);
	FILE* textFile = fopen(nameOfFile, "r");
	if (textFile == NULL) {
		printf("Can't open txt file\n");
		return 1;
	}
	searchWords(textFile, dictionaryWords, numberOfDictionaryWords, dictionaryWordsCounter);
	fclose(textFile);
	printf("dictionary words:\n");
	for (i = 0; i < numberOfDictionaryWords; i++) {
		printf(dictionaryWords[i]);
		printf("%d\n", dictionaryWordsCounter[i]);
	}
	for (i = 0; i < numberOfDictionaryWords; i++) {
		free(dictionaryWords[i]);
	}
	free(dictionaryWords);
	getchar();
	return 0;
}