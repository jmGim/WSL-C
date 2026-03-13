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
        unsigned long long t1, t2;
        t1 = rdtsc();
        result = recurAdd(num);
        t2 = rdtsc();
				printf("Sum Result = %lld\n", result);
        
        double duration = (t2 - t1) / 3000580;  // CPU Freq: 3000MHz

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

