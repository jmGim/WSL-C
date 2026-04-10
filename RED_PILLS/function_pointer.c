#include <stdio.h>

// 1. enum을 활용하여 연산자 정의
typedef enum {
    ADD = 0,
    SUB,
    MUL,
    DIV
} Operator;

// 사칙연산 함수들
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div_func(int a, int b) { return (b != 0) ? (a / b) : 0; }

// 2. 매크로 함수로 계산기 출력 포맷 정의
#define PRINT_RESULT(op, a, b, res) \
    printf("%d %s %d = %d\n", a, op, b, res)

int main() {
    int x = 10, y = 5;
    int result;

    // 3. 함수 포인터 배열 정의 (매크로 함수와 연계)
    int (*calc[])(int, int) = {add, sub, mul, div_func};
    const char* op_str[] = {"+", "-", "*", "/"};

    // 4. enum과 함수 포인터를 활용한 계산
    Operator currentOp = ADD;
    result = calc[currentOp](x, y);
    PRINT_RESULT(op_str[currentOp], x, y, result); // 매크로 사용

    currentOp = MUL;
    result = calc[currentOp](x, y);
    PRINT_RESULT(op_str[currentOp], x, y, result);

    return 0;
}

