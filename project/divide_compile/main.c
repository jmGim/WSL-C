#include <stdio.h>
#include "math.h"

// void input_data(int*, int*);  // 두 정수를 입력하는 함수 선언
// double average(int, int);     // 평균을 구하는 함수 선언

int count = 0;              // 입력한 양수의 수 누적
static int total = 0;       // 입력한 양수의 합

int main(void)
{
    int a, b;
    double avg;

    total = input_data();   // 양수를 입력하고 그 합을 반환
    avg = average();        // 평균 계산
    print_data(avg);

    printf("%d와 %d의 평균 : %.1lf\n", a, b, avg);  // 입력값과 평균 출력

    return 0;
}

