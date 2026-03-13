#include <stdio.h>

void fruit(int count);

int main(void)
{
    fruit(1);            // 처음 호출하므로 1을 인수로 준다.

    return 0;
}

void fruit(int count)    // 호출 횟수를 매개변수에 저장
{
    printf("apple\n");
    if (count == 3) return;     //재귀호출한 프로세스가 스택에 쌓여있는 데 쌓여 있는 프로세스 모두 뱉어냄(?) // 호출 횟수가 3이면 반환하고 끝낸다.
    fruit(count + 1);           // 재호출할 때 호출 횟수를 1 증가
}

