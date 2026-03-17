#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap(int* a, int* b);
int main() {
	int src[5] = { 1,2,3,4,5 };
	int dst[5] = {10, 20 ,30 ,40 ,50};
	int* ptrs = src;
	int* ptrd = dst;

	for (int i = 0; i < 5; i++) {
		swap(ptrs + i, ptrd + i);
	}

	printf("src : ");
	for (int i = 0; i < 5; i++) {
		printf(" %d ", *(ptrs + i));
	}
	printf("\n");

	printf("dst : ");
		for (int i = 0; i < 5; i++) {
		printf(" %d ", *(ptrd + i));
	}

	printf("\n");
	printf("Start : %p, End : %p, Distance : %ldbytes", ptrs, ptrs + 4, ((ptrs + 4) - ptrs) * sizeof(int));

}


void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
