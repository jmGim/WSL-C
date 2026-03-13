#include <stdio.h>
//#include <sys/time.h> // gettimeofday() 포함

unsigned long long recurAdd(unsigned long long n);

static inline unsigned long long rdtsc(void) {
    unsigned int lo, hi;
    // rdtsc 명령어 실행: 결과를 edx(hi)와 eax(lo)에 저장
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}



int main() {
        int num=100000;
        unsigned long long result;

	//struct timeval start, end;
    	//double duration;

	//gettimeofday(&start, NULL); // 시작
	//clock_t t1,t2;
	//t1 = clock();
	//for (int i = 0; i < 100000; i++);				      
	//t2 = clock();
	//
	unsigned long long t1, t2;
	t1 = rdtsc();
	result = recurAdd(num);

	//double duration = (t2 - t1) / 1000000;
	
	t2 = rdtsc();      

	//double duration = (t2 - t1) / 429455;
	double duration = (t2 - t1) / 3000580;
	//gettimeofday(&end, NULL); // 시작

	//duration = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;
        printf("Sum Result = %lld\n", result);
	
	printf("걸린 시간: %f ms\n", duration*1000);
	return 0;
}


unsigned long long recurAdd(unsigned long long n){
        if (n > 1) {
                return n + recurAdd(n -1);
        } else {
                return 1;
        }
}                    
