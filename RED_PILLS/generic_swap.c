// - **입력:** 두 변수의 주소 `void *a, void *b`, 데이터 크기 `size_t size`
// - **출력:** 두 변수의 값이 교환됨
// - **제약조건:** `malloc` 사용 금지, 바이트 단위 교환 알고리즘 사용.
// - **실행결과:** `a: 10, b: 20 -> a: 20, b: 10`

#include <stdio.h>
#include <stdint.h>
//#include <intrin.h>  // built-in-funcion

void swap_generic(void* vp1, void* vp2, size_t size) {
	// 1바이트 단위로 접근하기 위해 char*로 캐스팅
	unsigned char* p1 = (unsigned char*)vp1;
	unsigned char* p2 = (unsigned char*)vp2;
	unsigned char temp;

	// size 바이트만큼 하나씩 교환
	for (size_t i = 0; i < size; i++) {
		temp = p1[i];
		p1[i] = p2[i];
		p2[i] = temp;
	}
}

int main() {
	int a = 10, b = 20;
	printf("\n===  Day 9: 제네릭 Swap 함수 (void)* ===\n");
	printf("a : %d, b: %d \n", a, b);
	swap_generic(&a, &b, sizeof(int));

	printf("a : %d, b: %d \n", a, b);

	return 0;
}
