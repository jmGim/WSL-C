/*
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

// 소수 판별 함수: 소수이면 1, 아니면 0 반환

static int primeNum[100000];

int isPrime(int n) {
    if (n < 2) return 0; // 1 이하는 소수 아님
    for (int i = 2; i <= sqrt(n) ; i++) { // 제곱근까지만 검사 [9, 13]
        if (n % i == 0) return 0; // 나누어떨어지면 소수 아님
    }
    return 1; // 소수임
}

int main() {
    struct timeval start, end;
    // clock_t start, end;
    double result;
    
    //start = clock(); //
    gettimeofday(&start, NULL);		     //
	

    int num, i;
    printf("소수 판별할 숫자를 입력하세요: ");
    scanf("%d", &num);

    if (isPrime(num)) {
        printf("%d은(는) 소수입니다.\n", num);
    } else {
        printf("%d은(는) 소수가 아닙니다.\n", num);
    }

    // 2부터 입력한 수까지의 모든 소수 출력 예시
    int prime_count = 0;
    printf("2부터 %d까지의 소수: ", num);
    for (i = 2; i <= num; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
	    prime_count++;
        }
    }
    printf("\n");
    //end = clock();
    gettimeofday(&end, NULL);
    result = (double) (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec )/1000000;

    //printf("걸린 시간 : %.6f 초\n", result );
    printf("걸린 시간: %f 밀리초(ms)\n", result * 1000);
    printf("The Number of Prime Nums = %d\n", prime_count);
    return 0;
}
*/



#include <stdio.h>
#include <time.h>

#define MAX 1000000

int main() {
    int prime[MAX + 1];
    int i, j;
    int count = 0;
    int line = 0;

    clock_t start, end;

    start = clock();

    for (i = 0; i <= MAX; i++)
        prime[i] = 1;

    prime[0] = prime[1] = 0;

    for (i = 2; i * i <= MAX; i++) {
        if (prime[i]) {
            for (j = i * i; j <= MAX; j += i) {
                prime[j] = 0;
            }
        }
    }

    for (i = 2; i <= MAX; i++) {
        if (prime[i]) {
            printf("%5d ", i);
            count++;
            line++;

            if (line == 5) {
                printf("\n");
                line = 0;
            }
        }
    }

    end = clock();

    printf("\n\n소수 개수: %d\n", count);
    printf("걸린 시간: %lf 초\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
