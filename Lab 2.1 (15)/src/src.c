#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "src.h"



int getIntCommand(int lowBound, int highBound) {
	int command;
	char ch;
	while (scanf("%d%c", &command, &ch) != 2 || ch != '\n' || command < lowBound || command > highBound) {
		printf("Incorrect value, required integer from %d to %d, enter again: ", lowBound, highBound);
		while (getchar() != '\n');
	}
	return command;
}

void setDate(int* day, int* month, int* year) {
	char ch;
	int real;
	int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	do {
		while (scanf("%d%*c%d%*c%d%c", day, month, year, &ch) != 4 || ch != '\n') {
			printf("It is not a real date: ");
			while (getchar() != '\n');
		}
		real = 1;
		if (*year % 4 == 0) {
			monthDays[1] = 29;
		}
		else {
			monthDays[1] = 28;
		}
		if (*year < 1971) {
			printf("Year is too small, enter again: ");
			real = 0;
		} 
		else if (*year > 2500) {
			printf("Year is too big, enter again: ");
			real = 0;
		}
		else if (*month < 0 && *month > 12) {
			printf("Invalid month, enter again: ");
			real = 0;
		}
		else if (*day < 0 || *day > monthDays[*month - 1]) {
			printf("Invalid day, enter again: ");
			real = 0;
		}
	} while (real != 1);
}

int calculateLength(int beginDay, int beginMonth, int beginYear, int endDay, int endMonth, int endYear) {
	int possible = 1;
	if (endYear < beginYear) {
		possible = 0;
	} else if (endYear == beginYear) {
		if (endMonth < beginMonth) {
			possible = 0;
		}
		else if(endMonth == beginMonth) {
			if (endDay <= beginDay) {
				possible = 0;
			}
		}
	}
	int length = 0;
	int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (possible == 1) {
		while (endYear > beginYear) {
			if (endYear % 4 == 0) {
				length += 366;
			}
			else {
				length += 365;
			}
			endYear--;
		}
		if (endYear % 4 == 0) {
			monthDays[1] = 29;
		}
		if (endMonth > beginMonth) {
			while (endMonth > beginMonth) {
				length += monthDays[endMonth - 1];
				endMonth--;
			}
		}
		else if (endMonth < beginMonth) {
			while (endMonth < beginMonth) {
				length -= monthDays[endMonth - 1];
				endMonth++;
			}
		}
		length += (endDay - beginDay);
	}
	else {
		length = -1;
	}
	return length;
}

long long getProgrammersCost(int workLength, int  rate, int employeesNumber) {
	long long cost;
	if (workLength <= 0 || rate <= 0 || employeesNumber <= 0) {
		cost = -1;
	}
	else {
		cost = (long long)workLength * 8 * rate * employeesNumber;
	}
	return cost;
}