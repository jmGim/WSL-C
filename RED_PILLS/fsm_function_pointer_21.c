#include <stdio.h>

// 1. 상태(State)와 이벤트(Event) 열거형 정의
typedef enum {
    STATE_IDLE = 0,
    STATE_RUN,
    STATE_ERROR,
    NUM_STATES // 총 상태 개수 (배열 크기용)
} State;

typedef enum {
    EVT_BUTTON_PRESS = 0,
    EVT_TIMEOUT,
    EVT_RESET,
    NUM_EVENTS // 총 이벤트 개수 (배열 크기용)
} Event;

// 디버깅 및 출력을 위한 문자열 매핑 배열
const char* state_str[] = { "IDLE", "RUN", "ERROR" };
const char* event_str[] = { "EVT_BUTTON_PRESS", "EVT_TIMEOUT", "EVT_RESET" };

// 2. 상태 진입 시 실행될 액션 함수들 (함수 시그니처가 같아야 함)
void action_motor_run(void) {
    printf("   (Running... Motor spinning ⚙️)\n");
}

void action_system_halt(void) {
    printf("   (Waiting... ⚠️ System Halted)\n");
}

// [핵심 1] 액션 함수를 담을 수 있는 '함수 포인터' 타입 정의
typedef void (*ActionFunc)(void);

// 3. 상태 전이(Transition) 구조체
typedef struct {
    State next_state;   // 다음으로 이동할 상태
    ActionFunc action;  // 전이 시 실행할 함수 포인터 (없으면 NULL)
} Transition;

// [핵심 2] 2차원 상태 전이 테이블 (FSM Table)
// [현재_상태][발생_이벤트] 형식으로 O(1) 속도로 다음 상태를 찾아냅니다.
// C99의 지정 초기화자(Designated Initializer)를 사용하여 가독성을 극대화했습니다.
Transition fsm_table[NUM_STATES][NUM_EVENTS] = {
    // ---- [현재 상태: IDLE] ----
    [STATE_IDLE] = {
        [EVT_BUTTON_PRESS] = { STATE_RUN, action_motor_run }, // RUN으로 가고 모터 켬
        [EVT_TIMEOUT]      = { STATE_IDLE, NULL },            // 변화 없음
        [EVT_RESET]        = { STATE_IDLE, NULL }             // 변화 없음
    },
    // ---- [현재 상태: RUN] ----
    [STATE_RUN] = {
        [EVT_BUTTON_PRESS] = { STATE_RUN, NULL },             // 이미 RUN이므로 무시
        [EVT_TIMEOUT]      = { STATE_IDLE, NULL },            // 타임아웃 시 IDLE 복귀
        [EVT_RESET]        = { STATE_ERROR, action_system_halt } // 리셋 시 에러! 정지
    },
    // ---- [현재 상태: ERROR] ----
    [STATE_ERROR] = {
        [EVT_BUTTON_PRESS] = { STATE_ERROR, NULL },           // 에러 중 버튼 무시
        [EVT_TIMEOUT]      = { STATE_ERROR, NULL },           // 무시
        [EVT_RESET]        = { STATE_IDLE, NULL }             // 리셋해야만 IDLE 복귀
    }
};

// 현재 시스템의 상태를 저장하는 전역 변수
State current_state = STATE_IDLE;

// [핵심 3] 이벤트 처리기 (Dispatcher) - 분기문(switch-case)이 단 하나도 없습니다!
void dispatch_event(Event evt) {
    // 1. 표(Table)에서 현재 상태와 들어온 이벤트에 해당하는 셀(Cell)을 즉시 가져옵니다.
    Transition t = fsm_table[current_state][evt];

    // 2. 상태가 변했거나, 상태 변화는 없어도 실행할 액션이 있는 경우에만 처리
    if (t.next_state != current_state || t.action != NULL) {
        printf("--------------------------------------------------\n");
        printf("[TRANSITION] %s --(%s)--> %s\n", state_str[current_state], event_str[evt], state_str[t.next_state]);
        printf("--------------------------------------------------\n");

        // 3. 표에 등록된 액션 함수가 있다면 (NULL이 아니라면) 괄호()를 붙여 실행합니다.
        if (t.action != NULL) {
            t.action();
        }

        // 4. 상태 업데이트
        current_state = t.next_state;
    }
}

int main() {
    printf("IDLE ->(Button) -> RUN\n");
    printf("=== Day 21: Visual FSM Implementation ===\n");
    printf("Initial State: [%s]\n\n", state_str[current_state]);

    // 시나리오 1: 정상 구동 및 타임아웃
    dispatch_event(EVT_BUTTON_PRESS); // IDLE -> RUN (액션 출력 O)
    dispatch_event(EVT_TIMEOUT);      // RUN  -> IDLE

    // [고급 기법] 런타임 액션 변경 (함수 포인터의 강력한 장점)
    // 제시하신 출력 결과에 두 번째 'IDLE -> RUN'에서는 액션(모터 출력)이 없었습니다.
    // 함수 포인터 방식은 실행 중(Runtime)에 이렇게 동작을 동적으로 뺄 수 있습니다.
    fsm_table[STATE_IDLE][EVT_BUTTON_PRESS].action = NULL; 

    // 시나리오 2: 재구동 및 에러 발생
    dispatch_event(EVT_BUTTON_PRESS); // IDLE -> RUN (액션 출력 X, 위에서 NULL로 덮어썼기 때문)
    dispatch_event(EVT_RESET);        // RUN  -> ERROR
    dispatch_event(EVT_RESET);        // ERROR-> IDLE

    printf("\n>> Simulation Ended.\n");
    return 0;
}
