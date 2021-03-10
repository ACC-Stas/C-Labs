#include "main.h"
#include <stdio.h>
#include <limits.h>

int main() {
	int maxNumber, maxSum;
	maxNumber = maxFibonachi();
	maxSum = maxSumFibonachi();
	printf("Number of the biggest element of Fibonachi, that can be held in int variable is %d\n", maxNumber);
	printf("Max sum of Fibbonachi elements, that can be held in int variable is %d", maxSum);
	return 0;
}

int maxFibonachi() {   /*return number of the biggest element, that can be held in int variable*/ 
	int counter = 2, previousX = 1, previousY = 1, next = 0;
	while (INT_MAX - previousX >= previousY) {
		counter++;
		next = previousX + previousY;
		previousY = previousX;
		previousX = next;
	}
	return counter;
}

int maxSumFibonachi() {  /*return max sum of Fibbonachi elements, that can be held in int variable*/
	int previousX = 1, previousY = 1, next, sum;
	sum = previousX + previousY;
	do {
		next = previousX + previousY;
		previousY = previousX;
		previousX = next;
		sum += next;
	} while (INT_MAX - sum >= next);
	return sum;
}