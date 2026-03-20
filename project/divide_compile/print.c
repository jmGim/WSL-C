#include <stdio.h>

extern int total;
extern int count;

void print_data(double avg)
{
    printf("입력한 양수의 개수 : %d\n", count);
    printf("전체 합과 평균 : %d, %.1lf\n", total, avg);
}