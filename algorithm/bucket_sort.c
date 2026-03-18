#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>
#include <stdbool.h>

// 버킷 개수
#define SIZE 100000

void grandom(int arr[], int n, int max);
void bucketsort(int arr[], int n, int max);

int main(void) {
    srand(time(NULL));
    int arr[SIZE];
    clock_t start, end;

    // 1~100 범위 난수 10개 생성
    grandom(arr, 100000, 100);

    // 초기 배열 출력
    printf("초기 배열: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 버킷 정렬 함수로 데이터 배열과 버킷 갯수 함께 요청
    start = clock();
    bucketsort(arr, 10, 100000);
    end = clock();

    // 정렬된 결과 출력
    printf("정렬된 결과: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("수행 시간 : %.3lfs\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

// 난수 생성 함수
void grandom(int arr[], int n, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max + 1;
    }
}

// 버킷 정렬 함수
void bucketsort(int arr[], int n, int max) {
    int bucketCount = n;//버킷의 개수
    int bucketRange = max / bucketCount;//각 버킷의 범위
    int* buckets[n];
    int count[n] = {};

    // 버킷 메모리 동적 할당
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int*)malloc(n * sizeof(int));
    }

    // 분배
    for (int i = 0; i < n; i++) {
        int index = (arr[i] - 1) / bucketRange;
        buckets[index][count[index]++] = arr[i];
    }

    // 버킷 분배 결과 출력
    printf("\n--- 버킷 분배 결과 ---\n");
    for (int i = 0; i < bucketCount; i++) {
        printf("Bucket[%d]: ", i);
        for (int j = 0; j < count[i]; j++) {
            printf("%d ", buckets[i][j]);
        }
        printf("\n");
    }

    // 정렬 과정 출력
    printf("\n--- 각 버킷 정렬 과정 ---\n");
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 1; j < count[i]; j++) {
            int key = buckets[i][j];
            int k = j - 1;
            while (k >= 0 && buckets[i][k] > key) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = key;

            // 버킷 i의 현재 상태 출력
            printf("Bucket[%d] after step %d: ", i, j);
            for (int m = 0; m < count[i]; m++) {
                printf("%d ", buckets[i][m]);
            }
            printf("\n");
        }
    }
    printf("\n");

    // 정렬 상태 배열 저장
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < count[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
    }

    // 메모리 해제
    for (int i = 0; i < bucketCount; i++) {
        free(buckets[i]);
    }
}
