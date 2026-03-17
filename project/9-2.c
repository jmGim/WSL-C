#include <stdio.h>

int main(void)
{
    double a = 3.4;
    double* pd = &a;
    int *pi;
    pi=(int*)pd;
    
    //*pi = (int)*pd;  => 3.5를 3으로 형변환

    printf("*pi : %u\n", *pi);
    printf("*pd : %u\n", *pd);
    return 0;
}

