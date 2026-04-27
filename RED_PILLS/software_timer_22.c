//- **입력:** `SetTimer(ID, ms)`, `Tick()` 주기적 호출
//- **출력:** 시간 만료 시 콜백 함수 실행
//- **제약조건:** 단일 연결 리스트로 남은 시간 순으로 정렬하여 관리(Delta Time 방식).
//- 참고
    
//    "수많은 타이머를 어떻게 효율적으로 관리할 것인가?"에 대한 임베디드 시스템의 표준 해법입니다.
//    모든 타이머의 남은 시간을 매번 깎는 방식(O(N))은 타이머가 많아지면 시스템을 느리게 합니다.
 //   대신 **Delta Time(상대 시간)** 방식을 사용하면, 타이머 틱(Tick)마다 **맨 앞의 노드 하나만 깎으면(O(1))** 되므로 성능이 획기적으로 개선됩니다.
    
//    ---
    
//    ### 1. 핵심 원리: Delta Time (상대 시간)
    
//    타이머를 "만료될 절대 시간"이 아니라, "앞의 타이머가 터지고 나서 기다려야 할 시간"으로 저장합니다.
    
//    - **요청:** A(10ms), B(15ms), C(15ms)
//    - **저장(Linked List):** `Head -> [A: 10] -> [B: 5] -> [C: 0] -> NULL`
//        - A는 10초 뒤 만료.
//        - B는 A가 만료된 후 5초 뒤(총 15초) 만료.
//        - C는 B가 만료된 후 0초 뒤(즉시, 총 15초) 만료.


#include <stdio.h>
#include <stdlib.h>

typedef struct TimerNode {
    int id;
    int dt;                 
    struct TimerNode* next;
} TimerNode;

TimerNode* head = NULL;

void PrintTimerList() {
    TimerNode* curr = head;
    printf("[Timer List] ");
    if (curr == NULL) {
        printf("Empty\n");
        return;
    }
    int cumulative = 0;
    while (curr != NULL) {
        cumulative += curr->dt;
        printf("(ID:%d, dt:%d, total:%d) -> ", curr->id, curr->dt, cumulative);
        curr = curr->next;
    }
    printf("NULL\n");
}

void SetTimer(int id, int ms) {
    TimerNode* newNode = (TimerNode*)malloc(sizeof(TimerNode));
    newNode->id = id;
    newNode->next = NULL;

    printf("Timer %d set (%d ms) ", id, ms);


    if (head == NULL || ms < head->dt) {
        printf("[Inserted at HEAD]\n");
        if (head != NULL) {
            head->dt -= ms; 
        }
        newNode->dt = ms;
        newNode->next = head;
        head = newNode;
    } 

    else {
        printf("[Inserted in List]\n");
        TimerNode* curr = head;
        int remaining = ms;

        while (curr->next != NULL && remaining >= curr->next->dt) {
            remaining -= curr->dt;
            curr = curr->next;
        }
       

        remaining -= curr->dt; 
        newNode->dt = remaining;
        newNode->next = curr->next;
        curr->next = newNode;

        
        if (newNode->next != NULL) {
            newNode->next->dt -= newNode->dt;
        }
    }
    PrintTimerList();
}


void Tick(int current_tick) {
    if (head == NULL) return;

    head->dt--;
    printf("Tick %d: Rem Head dt: %d\n", current_tick, head->dt);

    while (head != NULL && head->dt <= 0) {
        printf(">> [Event] Timer %d expired! Action executed.\n", head->id);
        TimerNode* temp = head;
        head = head->next;
        free(temp);
        
        if (head != NULL) {
            printf("Next Rem Head dt: %d\n", head->dt);
        }
    }
}

int main() {
    printf("=== Day 22: Software Timer (Delta List) ===\n\n");


    SetTimer(1, 10);
    SetTimer(2, 5);
    SetTimer(3, 15);

    printf("\n>> Start Ticking...\n");


    for (int i = 1; i <= 15; i++) {
        Tick(i);
        if (head == NULL) {
            printf("All timers cleared.\n");
            break;
        }
    }

    return 0;
}
