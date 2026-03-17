#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000000   // 배열 크기
void bucketSort(int arr[], int n) {
    clock_t start = clock(), end;
    double elapsed;
    int max = 1000000;
    int bucketRange = 100000;
    int bucketCount = 10;

    int* buckets[10];
    int count[10];

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int*)malloc(n * sizeof(int));
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int index = arr[i] / bucketRange;
        if (index == 10) index--;
        buckets[index][count[index]++] = arr[i];
    }
    for (int i = 0; i < bucketCount; i++) {
        printf("bucket[%d] : ", i);
        for (int j = 0; j < 5; j++) {
            printf("%d ", buckets[i][j]);
        }
        printf("\n");
    }
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("실행 시간: %.3f초\n", elapsed);

    printf("\n");
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 1; j < count[i]; j++) {
            int key = buckets[i][j];
            int k = j - 1;

            while (k >= 0 && buckets[i][k] > key) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = key;
        }
    }

    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < count[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
    }
   
    for (int i = 0; i < bucketCount; i++) {
        printf("bucket[%d] : ", i);
        for (int j = 0; j < 5; j++) {
            printf("%d ", buckets[i][j]);
        }
        printf("\n");
    }
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("실행 시간: %.3f초\n", elapsed);
    printf("\n");
    for (int i = 0; i < bucketCount; i++)
        free(buckets[i]);
}

int rand20() {
    return ((rand() & 0x7FFF) << 5) | (rand() & 0x1F);
}

int main() {
    int* arr;
    clock_t start = clock(), end;
    double elapsed;
    srand(0); // 난수 시드 초기화

    // 동적 메모리로 정수 배열 할당
    arr = (int*)malloc(sizeof(int) * SIZE);
    if (arr == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // 난수로 배열 초기화
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand20() % SIZE + 1;
    }

    bucketSort(arr, SIZE);

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
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("실행 시간: %.3f초\n", elapsed);

    // 동적 메모리 해제
    free(arr);

    return 0;
}


