#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int getInt(int lowBound, int highBound) {
	int command;
	char ch;
	while (scanf("%d%c", &command, &ch) != 2 || ch != '\n' || command < lowBound || command > highBound) {
		printf("Incorrect value, required integer from %d to %d, enter again: ", lowBound, highBound);
		while (getchar() != '\n');
	}
	return command;
}

int*** project(int*** body, size_t zSize, size_t ySize, size_t xSize) { /*returns massive  with a body projected on the axis*/
	int*** projection = (int***)malloc(3*sizeof(int**)); /*0 - xy projection, 1 - xz, 2 - yz*/
	if (projection == NULL) {
		printf("\nCan't allocate memory\n");
		return NULL;
	}
	projection[0] = (int**)malloc(xSize * sizeof(int*));
	if (projection[0] == NULL) {
		free(projection);
		printf("\nCan't allocate memory\n");
		return NULL;
	}
	int i, j, g;
	projection[1] = (int**)malloc(xSize * sizeof(int*));
	if (projection[1] == NULL) {
		free(projection[0]);
		free(projection);
		printf("\nCan't allocate memory\n");
		return NULL;
	}
	for (i = 0; i < xSize; i++) {
		projection[0][i] = (int*)malloc(ySize * sizeof(int));
		projection[1][i] = (int*)malloc(zSize * sizeof(int));
		if (projection[0][i] == NULL || projection[1][i] == NULL) {
			int temp = i;
			if (projection[0][i] == NULL) {
				temp--;
			}
			if (projection[1][i] == NULL) {
				i--;
			}
			for (; temp >= 0; temp--) {
				free(projection[0][temp]);
			}
			for(; i >= 0; i--) {
				free(projection[1][i]);
			}
			free(projection);
			printf("\nCan't allocate memory\n");
			return NULL;
		}
	} 
	projection[2] = (int**)malloc(ySize * sizeof(int*));
	if (projection[2] == NULL) {
		for (i = xSize - 1; i >= 0; i--) {
			free(projection[0][i]);
		}
		for (j = ySize - 1; j >= 0; j--) {
			free(projection[1][j]);
		}
		free(projection[0]);
		free(projection[1]);
		free(projection);
		printf("\nCan't allocate memory\n");
		return NULL;
	}
	for (i = 0; i < ySize; i++) {
		projection[2][i] = (int*)malloc(zSize * sizeof(int));
		if (projection[2][i] == NULL) {
			for (g = xSize - 1; g >= 0; g--) {
				free(projection[0][g]);
			}
			for (j = ySize - 1; j >= 0; j--) {
				free(projection[1][j]);
			}
			i--;
			for (; i >= 0; i--) {
				free(projection[2][i]);
			}
			free(projection[0]);
			free(projection[1]);
			free(projection);
			printf("\nCan't allocate memory\n");
			return NULL;
		}
	}
	for (i = 0; i < xSize; i++) {
		for (j = 0; j < ySize; j++) {
			projection[0][i][j] = 0;
		}
		for (g = 0; g < zSize; g++) {
			projection[1][i][g] = 0;
		}
	}
	for (j = 0; j < ySize; j++) {
		for (g = 0; g < zSize; g++) {
			projection[2][j][g] = 0;
		}
	}
	int z, y, x;
	for (z = 0; z < zSize; z++) {
		for (y = 0; y < ySize; y++) {
			for (x = 0; x < xSize; x++) {
				if (body[z][y][x] != 0) {
					projection[0][x][y] = 1;
					projection[1][x][z] = 1;
					projection[2][y][z] = 1;
				}
			}
		}
	}

	return projection;
}