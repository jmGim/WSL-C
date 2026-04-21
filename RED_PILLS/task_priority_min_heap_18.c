//- **Day 18. 우선순위 큐 (Min Heap) - 태스크 스케줄링용**
//    - **입력:** (TaskID, Priority) 쌍 삽입, Pop 요청
//- **Day 18. 우선순위 큐 (Min Heap) - 태스크 스케줄링용**
//    - **입력:** (TaskID, Priority) 쌍 삽입, Pop 요청
//    - **출력:** 우선순위가 가장 높은(숫자가 낮은) TaskID 반환
//    - **제약조건:** 배열 기반 힙 구현.
//    - **실행결과:**
    
//    ```c
//    === Day 18: Task Scheduler (Min Heap) ===
//    
//    Tasks pushed: (1, 50), (2, 10), (3, 5), (5, 0), (4, 100)
//    Processing Tasks...
//    
//    >> Executing Task 5 (Priority 0)
//    >> Executing Task 3 (Priority 5)
//    >> Executing Task 2 (Priority 10)
//    >> Executing Task 1 (Priority 50)
//    >> Executing Task 4 (Priority 100)
//    
//   a ```   
//    입력 순서와 상관없이, **우선순위 숫자(0 → 5 → 10...)** 순서대로 정확하게 출력
 


#include <stdio.h>
#include <stdlib.h>

// 태스크 구조체 정의
typedef struct {
    int task_id;    // 태스크 번호
    int priority;   // 우선순위 (숫자가 낮을수록 높음)
} Task;

// 최소 힙(Min Heap) 관리자 구조체 정의
typedef struct {
    Task* array;    // 배열 포인터
    int capacity;   // 배열의 최대 크기
    int size;       // 현재 힙에 들어있는 태스크 개수
} MinHeap;

// 1. 힙 초기화
MinHeap* create_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (Task*)malloc(sizeof(Task) * capacity);
    return heap;
}

// 두 태스크의 위치를 바꾸는 유틸리티 함수
void swap(Task* a, Task* b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

// 2. 삽입 (Push) 및 Heapify Up
void push(MinHeap* heap, int task_id, int priority) {
    if (heap->size == heap->capacity) {
        printf("Heap is full!\n");
        return;
    }

    // 1) 배열의 맨 끝(가장 아래쪽 리프 노드)에 새 요소 삽입
    int current_idx = heap->size;
    heap->array[current_idx].task_id = task_id;
    heap->array[current_idx].priority = priority;
    heap->size++;

    // 2) Heapify Up (위로 끌어올리기)
    // 부모 노드 인덱스 = (현재 인덱스 - 1) / 2
    int parent_idx = (current_idx - 1) / 2;

    // 최소 힙 규칙: 부모의 우선순위 숫자가 자식(현재)보다 크면 자리를 바꾼다.
    // 루트 노드(0번)에 도달할 때까지 반복
    while (current_idx > 0 && heap->array[current_idx].priority < heap->array[parent_idx].priority) {
        swap(&heap->array[current_idx], &heap->array[parent_idx]);

        // 위치가 바뀌었으므로 인덱스 갱신
        current_idx = parent_idx;
        parent_idx = (current_idx - 1) / 2;
    }
}

// 3. 추출 (Pop) 및 Heapify Down
Task pop(MinHeap* heap) {
    // 힙이 비었을 때의 예외 처리용 더미 데이터
    if (heap->size <= 0) {
        Task empty = { -1, -1 };
        return empty;
    }

    // 1) 최상단(루트)에 있는 가장 우선순위가 높은 태스크를 빼냄
    Task root = heap->array[0];

    // 2) 배열의 맨 마지막에 있는 노드를 루트로 끌어올림
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    // 3) Heapify Down (아래로 내리기)
    int current_idx = 0;

    while (1) {
        // 왼쪽 자식 = 2 * i + 1, 오른쪽 자식 = 2 * i + 2
        int left_child = 2 * current_idx + 1;
        int right_child = 2 * current_idx + 2;
        int smallest = current_idx;

        // 왼쪽 자식이 존재하고, 현재 노드보다 우선순위 숫자가 더 작다면 (더 높은 우선순위라면)
        if (left_child < heap->size && heap->array[left_child].priority < heap->array[smallest].priority) {
            smallest = left_child;
        }
        // 오른쪽 자식이 존재하고, '지금까지 찾은 가장 작은 노드'보다도 더 작다면
        if (right_child < heap->size && heap->array[right_child].priority < heap->array[smallest].priority) {
            smallest = right_child;
        }

        // 부모(current_idx)가 자식들보다 이미 작다면 정렬 완료 (탈출)
        if (smallest == current_idx) {
            break;
        }

        // 더 작은 자식이 있다면 자리를 바꿈
        swap(&heap->array[current_idx], &heap->array[smallest]);
        current_idx = smallest;
    }

    return root; // 처음에 빼두었던 최상단 태스크 반환
}

int main() {
    printf("=== Day 18: Task Scheduler (Min Heap) ===\n\n");

    // 최대 10개를 담을 수 있는 힙 생성
    MinHeap* heap = create_heap(10);

    printf("Tasks pushed: (1, 50), (2, 10), (3, 5), (5, 0), (4, 100)\n");
    push(heap, 1, 50);
    push(heap, 2, 10);
    push(heap, 3, 5);
    push(heap, 5, 0); // 우선순위 0으로 가장 높음
    push(heap, 4, 100);

    printf("Processing Tasks...\n\n");

    // 힙이 빌 때까지 우선순위가 높은 순서대로 꺼내기
    while (heap->size > 0) {
        Task t = pop(heap);
        printf(">> Executing Task %d (Priority %d)\n", t.task_id, t.priority);
    }

    // 메모리 정리
    free(heap->array);
    free(heap);

    return 0;
}
   
