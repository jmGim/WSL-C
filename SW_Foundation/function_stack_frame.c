#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_LIMIT 10

int factorial(int n, int depth);

unsigned long g_pre_local_var = 0;
unsigned long diff = 0;

int main() {
	int N;
	printf("N : ");
	scanf("%d", &N);
	printf("%d! = %d\n", N, factorial(N, 1));

}

int factorial(int n, int depth) {
	int local_var = n; // 스택 확인용 지역 변수

	printf("Depth %d: Addr of n = %p  N = %d\n", depth, (unsigned long*)&local_var, n);

	if (depth > MAX_LIMIT) return -1; // Stack Guard
	if (n == 2) {
		g_pre_local_var = (unsigned long)&local_var;
	}
	if (n <= 1) {
		printf("Result = %p(%lu bytes)\n", ( (void *) (g_pre_local_var) - (unsigned long)(&local_var) ), (g_pre_local_var)-(unsigned long)(&local_var));
		return 1;
	}
	return n * factorial(n - 1, depth + 1);
}
