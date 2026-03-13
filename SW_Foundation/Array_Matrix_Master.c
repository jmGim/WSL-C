#include <stdio.h>

int main() {
	int Input[5][5] = { 1, 2, 3, 0, 1, 
						0, 1, 2, 3, 0, 
						1, 0, 1, 2, 3, 
						3, 2, 1, 0, 1, 
						0, 1, 2, 3, 0 } ;
	int Kernel[3][3] = { 1, 0, 1,
						0, 1, 0,
						1, 0, 1 } ;
	int Output[3][3] = {0, 0, 0,
						0, 0, 0,
						0, 0, 0};

	int i = 0, j = 0, k = 0, l = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			
			for (k = 0;  k < 3 ; k++) {
				for (l = 0; l < 3; l++) {
					Output[i][j] += Input[i + k][j + l] * Kernel[k][l];
				}
			}
		}
	}

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%3d", Output[i][j]);
		}
		printf("\n");
	}
}
