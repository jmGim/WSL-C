
#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>

#define MAX_LIMIT 10

int factorial(int n, int depth);

int main() {
    int N;

    scanf("%d", &N);
    printf("%d\n", factorial(N, MAX_LIMIT));
    
}

int factorial(int n, int depth) {
    int local_var = n; // 스택 확인용 지역 변수
    printf("Depth %d: Addr of n = %p\n", depth, (void*)&n);
    
    if (depth > MAX_LIMIT) return -1; // Stack Guard
    if (n <= 1) return 1;
    return n * factorial(n - 1, depth + 1);
}