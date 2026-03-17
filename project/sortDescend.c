#include <stdio.h>

void swap(int *a, int *b);

int main() {
	
	float temp;
	float arr[3];
	float *pa = arr;

	printf("실수값 3개 입력 : ");
	scanf("%f %f %f", &arr[0], &arr[1], &arr[2]);
	printf("\n");

	for (int i = 0; i < sizeof(arr) - 1; i++) { 
		for ( int j = 0; j < sizeof(arr) - i - 1; j++) { 
			if ( *(pa+j) < *(pa + j + 1))  {
				temp = *(pa+j);
				*(pa+j) = *(pa+j+1);
				*(pa+j+1) = temp;
			}
		}
		
	}

	printf("정렬된 값 출력 : %.1f, %.1f, %.1f\n", *(pa+0), *(pa+1), *(pa+2));

	return 0;
}


void swap(int *a, int *b){
	float temp;	
	for (int i = 0; i < 4; i++) { 
		for ( int j = 0; j < 4-i; j++) { 
			if ( *a < *b )  {
				temp = *a;
				*b = *a;
				*a = temp;
			}
		}
	}

}
