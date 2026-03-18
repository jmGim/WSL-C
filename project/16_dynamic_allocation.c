#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
	clock_t start, end;
	double duration;

	int i, j;                        // 반복 제어 변수
	int *prime_alloc;
	int prime_number = 0;
	int prime_count = 0;
	int line = 0;
	
	printf("양수 입력 : "); 
	scanf("%d", &prime_number);

	start = clock();
	prime_alloc = (int*)malloc(prime_number * sizeof(int));
	
	for (i = 0; i < prime_number; i++)
	{
		prime_alloc[i] = 1;
	}
	
	prime_alloc[0] = 0;
	prime_alloc[1] = 0;

	for (i = 2; i * i <= prime_number; i++) {
        	if (prime_alloc[i]) {
            	for (j = i * i; j <= prime_number; j += i) {
                	prime_alloc[j] = 0;
            	}
        	}
    	}

    	for (i = 1; i <= prime_number; i++) {
        	if (prime_alloc[i]) {
            	    printf("%5d ", i);
		} else { 
		    printf("    X ");
		}
		prime_count++;
		line++;

            	if (line == 5) {
               	    printf("\n");
               	    line = 0;
        	}
    	}
	free(prime_alloc);
	end = clock();

	duration = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("CPU 소요 시간: %f 초\n", duration);
	
	return 0;
}
