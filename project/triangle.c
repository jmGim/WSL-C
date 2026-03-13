#include<stdio.h>

int main(){
	int a;
	printf("삼각형의 높이를 입력하세요: ");
	scanf("%d", &a);

	for(int i=0;i<a;i++){
		for(int j=0;j<a-i-1;j++){
			printf(" ");
		}
		for(int j=0;j<i*2+1;j++){
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
 
