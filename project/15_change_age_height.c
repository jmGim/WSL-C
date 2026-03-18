#include <stdio.h>

// memcpy 없이 void 포인터를 이용한 swap 함수
void swap_void(void* a, void* b, size_t size) {
	// 1. void 포인터를 1바이트 단위인 char 포인터로 캐스팅
	char* pA = (char*)a;
	char* pB = (char*)b;
	char temp;

	// 2. 바이트 단위로 하나씩 맞교환 (size만큼 반복)
	for (size_t i = 0; i < size; i++) {
		temp = pA[i];
		pA[i] = pB[i];
		pB[i] = temp;
	}
}

int main() {
	// --- int swap ---
	int age1 = 0;
	int age2 = 0;                           // int형 변수
	double height1 = 0.00;
	double height2 = 0.00;                       // double형 변수
	
	printf("첫 번째 사람의 나이와 키 입력 : ");
	scanf("%d %lf", &age1, &height1);
	printf("두 번째 사람의 나이와 키 입력 : ");
	scanf("%d %lf", &age2, &height2);

	swap_void(&age1, &age2, sizeof(int));
	swap_void(&height1, &height2, sizeof(double));


	printf("첫 번째 사람의 나이와 키 : %d, %lf \n", age1, height1);
	printf("두 번째 사람의 나이와 키 : %d, %lf \n", age2, height2);

	return 0;
}

