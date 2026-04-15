// - **입력:** 행(row) 수, 열(col) 수
// -  **출력:** 연속된 메모리 공간을 갖는 2차원 배열 구조
// - **제약조건:** `malloc` 호출 횟수를 최소화할 것 (데이터 영역은 한 번에 할당).
// - **실행결과:**

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
	int row, col;
	scanf("%d %d", &row, &col);
	
	int** ppArr2D = (int**)malloc(sizeof(int*) * row );
	
	ppArr2D[0] = (int*)malloc(sizeof(int) * row * col);
	for (int i = 1; i < row; i++) {
		ppArr2D[i] = ppArr2D[i - 1] + col; 

	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			*(*(ppArr2D + i) + j) = i * col + j;
 			printf("%4d", *(*(ppArr2D+i)+j) + 1);
		}
		printf("  %p\n\n", (void *)*(ppArr2D+i));
		printf("\n");
	}

	free(ppArr2D[0]);
	free(ppArr2D);

	return 0;
}
