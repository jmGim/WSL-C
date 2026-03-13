#include <stdio.h>


int main() {

        char cal_formula[10];
        int num1, num2;
        char cal[3];
        int result = 0;

        printf("사칙연산 입력(정수) : ");
        
        scanf( "%d%s%d", &num1, &cal, &num2);

        switch (cal) {
                case('+') : {
                        result = num1 + num2;
                        break;
                }

                case('-') : {

                        result = num1 - num2;
                        break;
                }
                case('*') :{
                        result = num1 * num2;
                        break;
                }
                case('/') : {
                        return num1 / num2;
                        break;
                }
		default : {
			printf("Error");
			return 0;
		}

        }
        printf("%d %c %d = %d\n", num1, cal, num2, result);

}
