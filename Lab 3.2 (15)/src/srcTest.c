#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "src.h"

void testProjection() {
	int*** body;
	int zSize = 3;
	body = (int***)malloc(zSize * sizeof(int**));
	if (body == NULL) {
		printf("\nCan't allocate memory\n");
		exit(1);
	}
	int ySize = 2;
	int i, j, g;
	for (i = 0; i < zSize; i++) {
		body[i] = (int**)malloc(ySize * sizeof(int*));
		if (body[i] == NULL) {
			printf("\nCan't allocate memory\n");
			exit(1);
		}
	}
	int xSize = 4;
	for (i = 0; i < zSize; i++) {
		for (j = 0; j < ySize; j++) {
			body[i][j] = (int*)malloc(xSize * sizeof(int));
			if (body[i][j] == NULL) {
				printf("\nCan't allocate memory\n");
				exit(1);
			}
		}
	}
	for (i = 0; i < zSize; i++) {
		for (j = 0; j < ySize; j++) {
			for (g = 0; g < xSize; g++) {
				body[i][j][g] = 0;
			}
		}
	}
	body[0][0][3] = 1;
	body[0][1][3] = 1;
	body[1][0][0] = 1;
	body[1][0][1] = 1;
	body[1][0][2] = 1;
	body[1][1][0] = 1;
	int xyProjection[4][2];
	for (i = 0; i < xSize; i++) {
		for (j = 0; j < ySize; j++) {
			xyProjection[i][j] = 0;
		}
	}
	xyProjection[0][0] = 1;
	xyProjection[0][1] = 1;
	xyProjection[1][0] = 1;
	xyProjection[2][0] = 1;
	xyProjection[3][0] = 1;
	xyProjection[3][1] = 1;
	int xzProjection[4][3];
	for (i = 0; i < xSize; i++) {
		for (g = 0; g < zSize; g++) {
			xzProjection[i][g] = 0;
		}
	}
	xzProjection[0][1] = 1;
	xzProjection[1][1] = 1;
	xzProjection[2][1] = 1;
	xzProjection[3][0] = 1;
	int yzProjection[2][3];
	for (j = 0; j < ySize; j++) {
		for (g = 0; g < zSize; g++) {
			yzProjection[j][g] = 0;
		}
	}
	yzProjection[0][0] = 1;
	yzProjection[0][1] = 1;
	yzProjection[1][0] = 1;
	yzProjection[1][1] = 1;
	int*** answer;
	int temp1;
	int temp2;
	answer = project(body, 3, 2, 4);
	for (i = 0; i < xSize; i++) {
		for (j = 0; j < ySize; j++) {
			temp1 = xyProjection[i][j];
			temp2 = answer[0][i][j];
			assert(xyProjection[i][j] == answer[0][i][j]);
		}
	}
	for (i = 0; i < xSize; i++) {
		for (g = 0; g < zSize; g++) {
			assert(xzProjection[i][g] == answer[1][i][g]);
		}
	}
	for (j = 0; j < ySize; j++) {
		for (g = 0; g < zSize; g++) {
			assert(yzProjection[j][g] == answer[2][j][g]);
		}
	}
}

int main() {
	testProjection();
	return 0;
}