#include <stdio.h>

#define SUM(a,b) (a+b)  // 괄호 없으면 SUM a  + b적용
#define MUL(a,b) (a*b)

int main(){
    int a=10, b =20;
    int x=30, y=40;
    int res;


    printf("a+b = %d\n", SUM(a,b));
    printf("x*y = %d\n", MUL(x, y));
    res=10/SUM(2,3);
    printf("res = %d\n", res);

    return 0;
}