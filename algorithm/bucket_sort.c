#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000000   // 배열 크기
#define bucketRange 100000
#define bucketCount 100
void bucketSort(int arr[], int n) {
    clock_t start = clock(), end;
    double elapsed;
    
    // int bucketRange = 10000;
    // int bucketCount = 1000;

    int* buckets[bucketCount];
    int count[bucketCount];
    
    // [추가됨] 각 버킷에 '현재 할당된 메모리 용량'을 기억하는 배열
    int capacity[bucketCount]; 
    
    // 처음에는 버킷당 데이터 1000개 정도 들어갈 공간만 작게 할당합니다.
    int initialCapacity = 10000; 

    // 1. 메모리 초기 할당 (효율적 개선)
    for (int i = 0; i < bucketCount; i++) {
        // 기존: n(100만) * sizeof(int) -> 수정: 1000 * sizeof(int)
        // 메모리 사용량이 극적으로 줄어듭니다.
        buckets[i] = (int*)malloc(initialCapacity * sizeof(int));
        count[i] = 0;
        capacity[i] = initialCapacity; // 초기 용량 기록
    }

    // 2. 데이터를 버킷에 분배하며, 공간 부족 시 확장 (Scattering)
    for (int i = 0; i < n; i++) {
        int index = arr[i] / bucketRange;
        if (index == bucketCount) index--;

        // [핵심 로직] 해당 버킷에 데이터가 꽉 찼는지 확인
        if (count[index] >= capacity[index]) {
            // 꽉 찼다면 용량을 2배로 늘립니다.
            capacity[index] *= 2; 
            
            // realloc: 기존 데이터를 유지한 채로 메모리 공간만 더 넓게 재할당합니다.
            buckets[index] = (int*)realloc(buckets[index], capacity[index] * sizeof(int));
            
            // 메모리 재할당 실패 대비 안전장치
            if (buckets[index] == NULL) {
                printf("메모리 재할당 실패!\n");
                exit(1); 
            }
        }
        
        // 안전하게 데이터 삽입 및 카운트 증가
        buckets[index][count[index]++] = arr[i];
    }

    // ---------------------------------------------------------
    // 아래의 정렬 및 병합 로직은 기존 코드와 100% 동일합니다.
    // ---------------------------------------------------------

    // 3. 각 버킷 내부 정렬 (삽입 정렬)
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

    // 4. 정렬된 버킷을 병합
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < count[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
    }
    
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n버킷 정렬 실행 시간: %.3f초\n\n", elapsed);

    // 5. 동적 메모리 해제
    for (int i = 0; i < bucketCount; i++) {
        free(buckets[i]);
    }
}

// 사용자 정의 난수 발생 함수
int rand20() {
    return ((rand() & 0x7FFF) << 5) | (rand() & 0x1F);
}

int rand24() {
    return ((rand() & 0x7FFF) << 9) | (rand() & 0x1FF);
}

int main() {
    int* arr;
    clock_t start = clock(), end;
    double elapsed;
    srand(0); // 난수 시드 초기화

    // 메인 배열 할당
    arr = (int*)malloc(sizeof(int) * SIZE);
    if (arr == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // 난수 초기화
    for (int i = 0; i < SIZE; i++) {
        // arr[i] = rand20() % SIZE + 1;
        arr[i] = rand24() % SIZE + 1;
    }

    bucketSort(arr, SIZE);

    // 결과 앞 10개 확인
    printf("1~%d : ", bucketRange);
    for (int i = 0; i < bucketRange; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 결과 뒤 10개 확인
    printf("%d~%d : ", SIZE - bucketRange, SIZE);
    for (int i = SIZE - bucketRange; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("전체 프로그램 실행 시간: %.3f초\n", elapsed);

    // 메인 배열 해제
    free(arr);

    return 0;
}