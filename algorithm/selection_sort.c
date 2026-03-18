#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define SIZE 1000000
#define SIZE 100000  

int selection_sort(int* arr, int size);

int advanced_selection_sort(int* arr, int size);

// 배열 크기
int* make_dataset(int size);
void print_dataset(int* arr);
int main() {
	int* arr;
    clock_t start, end;      // 시간 측정 변수 선언
    double duration;         // 경과 시간(초)

    start = clock();         // 정렬 시작 직전 시간 저장
    arr=make_dataset(SIZE);
    end = clock();           // 정렬 완료 직후 시간 저장
    duration = (double)(end - start) / CLOCKS_PER_SEC; // 초 단위로 변환
    printf("make_dataset() 소요 시간: %f초\n", duration);

    print_dataset(arr);

    
    start = clock(); 
    selection_sort(arr, SIZE);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("selection_sort 소요 시간: %f초\n", duration);
    

    start = clock();
    advanced_selection_sort(arr, SIZE);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("advanced_selection_sort 소요 시간: %f초\n", duration);

    print_dataset(arr);

    // 동적 메모리 해제
    free(arr);

    return 0;
}

int selection_sort(int* arr, int size)
{
	int i, j, temp;
	for (i = 0; i < size - 1; i++) {
		for (j = i + 1; j < size; j++) {
			if (arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return 0;
}

int advanced_selection_sort(int* arr, int size)
{
	int i,j, temp;
	int min;
	for (i = 0; i < size-1; i++) {
		min = i;
        for (j = i + 1; j < size; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}			
		}
		if (min != i){
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}

	//for (i=0;i<size;i++)
	//{
	//	printf("%7d ", arr[i]);
 //       if(i%10==9) printf("\n");
	//}
	return 0;
}

int* make_dataset(int size)
{
    int* arr;
    srand(0); // 난수 시드 초기화

    // 동적 메모리로 정수 배열 할당
    arr = (int*)malloc(sizeof(int) * size);
    if (arr == NULL) {
        printf("메모리 할당 실패\n");
        return NULL;
    }

    // 난수로 배열 초기화
    for (int i = 0; i < SIZE; i++) {
        //arr[i] = rand() % (SIZE + 1); // rand()=> 32768 16bit까지만 표현
        arr[i] = ((rand() << 15) | rand()) % (size + 1);
    }
    
    return arr;
}

void print_dataset(int* arr)
{
    // 앞 10개만 출력
    printf("1~10 : ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("%d~%d : ", SIZE - 10, SIZE);
    for (int i = SIZE - 10; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

