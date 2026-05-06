// - **입력:** 태스크 3개 등록
// - **출력:** 태스크가 순차적으로 실행되고 양보(`yield`)하는 로그
// - **제약조건:** `setjmp`, `longjmp`를 사용하여 컨텍스트 스위칭 흉내 내기.

#include <stdio.h>
#include <setjmp.h>

// 스케줄러 본부로 돌아오기 위한 전역 세이브 포인트
jmp_buf scheduler_buf;

// --------------------------------------------------------
// [Task A] 2단계의 상태를 가지는 태스크
// --------------------------------------------------------
void task_a() {
    static int state = 0; // 함수가 종료되어도 값을 기억하는 static 변수

    if (state == 0) {
        printf("[Task A] Start working... (Step 1)\n");
        state = 1; // 다음 실행 시 수행할 상태 업데이트
    } else {
        printf("[Task A] Resumed working... (Step 2)\n");
        state = 0; // 다시 처음 상태로 초기화
    }
    
    // 할 일을 마쳤으니 스케줄러(main)로 제어권을 양보 (Yield)
    longjmp(scheduler_buf, 1); 
}

// --------------------------------------------------------
// [Task B] 상태 변화 없이 매번 같은 동작을 하는 태스크
// --------------------------------------------------------
void task_b() {
    printf("  [Task B] Processing Data...\n");
    
    // 제어권 양보 (Yield)
    longjmp(scheduler_buf, 1); 
}

// --------------------------------------------------------
// [Task C] 3단계의 상태를 가지는 태스크
// --------------------------------------------------------
void task_c() {
    static int state = 0;

    if (state == 0) {
        printf("    [Task C] Initialization\n");
        state = 1;
    } else if (state == 1) {
        printf("    [Task C] Calculation\n");
        state = 2;
    } else {
        printf("    [Task C] Finalize\n");
        state = 0;
    }
    
    // 제어권 양보 (Yield)
    longjmp(scheduler_buf, 1); 
}

// --------------------------------------------------------
// 메인 스케줄러 (Dispatcher)
// --------------------------------------------------------
int main() {
    // longjmp 복원 시 캐시(레지스터) 롤백 현상을 막기 위해 반드시 volatile 선언
    volatile int step = 0;          
    volatile int current_task = 0;  

    printf("=== Day 29: Simple Cooperative Scheduler ===\n\n");

    // [세이브 포인트] 태스크들이 longjmp를 호출하면 무조건 여기로 순간이동합니다.
    setjmp(scheduler_buf);

    // 총 10번의 스텝(출력결과 기준)이 실행되면 시뮬레이션 종료
    if (step >= 10) {
        printf("\n>> Simulation Finished.\n");
        return 0;
    }

    step++; // 스텝 카운터 증가

    // 라운드 로빈(Round-Robin) 방식으로 순서대로 태스크 호출
    if (current_task == 0) {
        current_task = 1; // 다음 차례를 B로 설정하고
        task_a();         // Task A 실행
    } 
    else if (current_task == 1) {
        current_task = 2; // 다음 차례를 C로 설정하고
        task_b();         // Task B 실행
    } 
    else if (current_task == 2) {
        current_task = 0; // 다시 차례를 A로 설정하고
        task_c();         // Task C 실행
    }

    return 0;
}
