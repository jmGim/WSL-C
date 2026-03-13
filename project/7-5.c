#include <stdio.h>

void fruit(void);           // 함수 선언
void fruit2(void);
int i=0;
int j=0;
int main(void)
{
    fruit();
                    // 함수 호출
    fruit2();
    return 0;
}

void fruit(void)            // 재귀호출 함수 정의
{   i++;
    printf("%d : apple\n",i);
    printf("%d : apple\n",i);
    fruit();                // 자신을 다시 호출
}
void fruit2(void)           // 재귀호출 함수 정의
{   j++;
    printf("%d : bannana\n",i);
    fruit2();               // 자신을 다시 호출
}

 
