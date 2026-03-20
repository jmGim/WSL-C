#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int advanced_selection_sort(int* arr, int size);


int main(void)
{
        clock_t start, end;
        double duration;
        int i, j;                        // 반복 제어 변수
        int *alloc_N;
        int N = 0;

	double average = 0;
	int max_num = 0;

        printf("양수 입력 : ");
        scanf("%d", &N);

        //start = clock();
        alloc_N = (int*)malloc(N * sizeof(int));
	if (alloc_N == NULL) {
        	printf("메모리 할당 실패\n");
        	return 1;
   	}

        for (i = 0; i < N; i++){
	    scanf("%d", alloc_N+i);
	}	
        //scanf("%d %d %d %d", alloc_N+0, alloc_N+1, alloc_N+2, alloc_N+3 );
	
        

	printf("\n");


        for (i = 0; i < N; i++) {
                average += *(alloc_N+i);
        }
	average /= N;

	max_num = advanced_selection_sort(alloc_N, N);
	
	printf("Average : %.1f, Max : %d\n", average, max_num);
	printf("Allocated at : %16p / \n", alloc_N);
        
	if (alloc_N != NULL) {
	    free(alloc_N);
	    alloc_N = NULL;
	}
	free(alloc_N);
	printf("Memoery freed successfully.\n");

	//end = clock();

        //duration = ((double) (end - start)) / CLOCKS_PER_SEC;
        //printf("CPU 소요 시간: %f 초\n", duration);

        return 0;
}



int advanced_selection_sort(int* arr, int size)
{
	int i,j, temp;
	int max;
	for (i = 0; i < size-1; i++) {
		max = i;
        for (j = i + 1; j < size; j++) {
			if (arr[max] < arr[j]) {
				max = j;
			}
		}
		if (max != i){
			temp = arr[i];
			arr[i] = arr[max];
			arr[max] = temp;
		}
	}

	return arr[0];
}
