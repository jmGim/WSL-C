#include <stdio.h> 

static int num1;
static int num2;

void swap(int* p1, int* p2);

int main() { 
	printf("두 정수 입력 : ");
	scanf("%d,%d", &num1, &num2);
	
	swap(&num1, &num2);

    	// printf("[Swap 후] num1: %d, num2: %d\n", num1, num2);

	printf("두 정수 출력 : %d,%d\n", num1, num2);

    	return 0;
}

// 포인터를 사용한 Swap 함수 정의
void swap(int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
