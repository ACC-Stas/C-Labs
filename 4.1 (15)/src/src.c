#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "src.h"

int getInt(int lowBound, int highBound) {
	int command;
	char ch;
	while (scanf("%d%c", &command, &ch) != 2 || ch != '\n' || command < lowBound || command > highBound) {
		printf("Incorrect value, required integer from %d to %d, enter again: ", lowBound, highBound);
		while (getchar() != '\n');
	}
	return command;
}

void swapLetters(char* str) { /*to move the last letter to the beginning of each word*/
	char lastLetter;
	int firstLetterPosition;
	int inWord = 0;
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
			if (inWord == 0) {
				firstLetterPosition = i;
			}
			inWord = 1;
		}
		else {
			if (inWord == 1) {
				lastLetter = str[i - 1];
				str[i - 1] = str[firstLetterPosition];
				str[firstLetterPosition] = lastLetter;
			}
			inWord = 0;
		}
	}
	if (inWord) {
		lastLetter = str[i - 1];
		str[i - 1] = str[firstLetterPosition];
		str[firstLetterPosition] = lastLetter;
	}
}

void deleteExcessLetters(char* str) { /*leave only the first occurrences of each letter in the words*/
	char lastLetter;
	int firstLetterPosition, lastLetterPostion;
	int inWord = 0;
	int i, j;
	int visitedLetters[52];
	int counter = 0; /*represents number of deleted elements*/
	for (i = 0; str[i] != '\0'; i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
			if (inWord == 0) {
				firstLetterPosition = i;
			}
			inWord = 1;
		}
		else {
			if (inWord == 1) {
				for (j = 0; j < 52; j++) {
					visitedLetters[j] = 0;
				}
				lastLetterPostion = i - 1;
				int shift;
				for (j = firstLetterPosition; j <= lastLetterPostion; j++) {
					if (str[j] >= 'A' && str[j] <= 'Z') {
						shift = 65;
					}
					else {
						shift = 71;
					}
					if (visitedLetters[str[j] - shift] == 0) {
						visitedLetters[str[j] - shift] = 1;
						str[j - counter] = str[j];
						if (counter != 0) {
							str[j] = ' ';
						}
					}
					else {
						str[j] = ' ';
						counter++;
					}
				}
			}
			inWord = 0;
		}
	}
	if (inWord == 1) {
		for (j = 0; j < 52; j++) {
			visitedLetters[j] = 0;
		}
		lastLetterPostion = i - 1;
		int counter = 0; /*represents number of deleted elements*/
		int shift;
		for (j = firstLetterPosition; j <= lastLetterPostion; j++) {
			if (str[j] >= 'A' && str[j] <= 'Z') {
				shift = 65;
			}
			else {
				shift = 71;
			}
			if (visitedLetters[str[j] - shift] == 0) {
				visitedLetters[str[j] - shift] = 1;
				str[j - counter] = str[j];
				if (counter != 0) {
					str[j] = ' ';
				}
			}
			else {
				str[j] = ' ';
				counter++;
			}
		}
	}
}