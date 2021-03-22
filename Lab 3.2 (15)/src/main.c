#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "src.h"

int main() {
	printf("Enter z-size from 2 to 10: ");
	int*** body;
	int zSize = getInt(2, 10);
	body = (int***)malloc(zSize*sizeof(int**));
	if (body == NULL) {
		printf("\nCan't allocate memory\n");
		return 1;
	}
	printf("\nEnter y-size from 2 to 10: ");
	int ySize = getInt(2, 10);
	int i, j, g;
	for (i = 0; i < zSize; i++) {
		body[i] = (int**)malloc(ySize*sizeof(int*));
		if (body[i] == NULL) {
			printf("\nCan't allocate memory\n");
			return 1;
		}
	}
	printf("\nEnter x-size from 2 to 10: ");
	int xSize = getInt(2, 10);
	for (i = 0; i < zSize; i++) {
		for (j = 0; j < ySize; j++) {
			body[i][j] = (int*)malloc(xSize*sizeof(int));
			if (body[i][j] == NULL) {
				printf("\nCan't allocate memory\n");
				return 1;
			}
		}
	}
	for (i = 0; i < zSize; i++) {
		for (j = 0; j < ySize; j++) {
			for (g = 0; g < xSize; g++) {
				body[i][j][g] = getInt(0, 1);
			}
		}
	}
	printf("You have entered:\n");
	for (i = 0; i < zSize; i++) {
		printf("List %d\n", i);
		for (j = 0; j < ySize; j++) {
			for (g = 0; g < xSize; g++) {
				printf("%d ", body[i][j][g]);
			}
			printf("\n");
		}
	}
	int*** projection = project(body, zSize, ySize, xSize);
	printf("xyProjection: \n");
	for (i = 0; i < xSize; i++) {
		for (j = 0; j < ySize; j++) {
			printf("%d ", projection[0][i][j]);
		}
		printf("\n");
	}
	printf("xzProjection: \n");
	for (i = 0; i < xSize; i++) {
		for (g = 0; g < zSize; g++) {
			printf("%d, ", projection[1][i][g]);
		}
		printf("\n");
	}
	printf("yzProjection: \n");
	for (j = 0; j < ySize; j++) {
		for (g = 0; g < zSize; g++) {
			printf("%d, ", projection[2][j][g]);
		}
		printf("\n");
	}
	for (i = 0; i < zSize; i++) {
		for (j = 0; j < ySize; j++) {
			free(body[i][j]);
		}
		free(body[i]);
	}
	free(body);
	for (i = 0; i < xSize; i++) {
		free(projection[0][i]);
		free(projection[1][i]);
	}
	for (i = 0; i < ySize; i++) {
		free(projection[2][i]);
	}
	for (i = 0; i < 2; i++) {
		free(projection[i]);
	}
	free(projection);
	return 0;
}