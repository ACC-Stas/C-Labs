#include "main.h"
#include <stdio.h>

int main() {
	int maxNumber, maxSum;
	maxNumber = maxFibonachi();
	maxSum = maxSumFibonachi();
	printf("Number of the biggest element of Fibonachi, that can be held in int variable is %d\n", maxNumber);
	printf("Max sum of Fibbonachi elements, that can be held in int variable is %d", maxSum);
	return 0;
}

int maxFibonachi() {   /*return number of the biggest element, that can be held in int variable*/ 
	int counter = 1, previousX = 1, previousY = 1, next = 0;
	do {
		counter++;
		next = previousX + previousY;
		previousY = previousX;
		previousX = next;
	} while (next >= 0);
	return counter;
}

int maxSumFibonachi() {  /*return max sum of Fibbonachi elements, that can be held in int variable*/
	int previousX = 1, previousY = 1, next, sum, temp;
	sum = previousX + previousY;
	do {
		temp = sum;
		next = previousX + previousY;
		previousY = previousX;
		previousX = next;
		sum += next;
	} while (sum >= 0);
	return temp;
}