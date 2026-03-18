#include <stdio.h>

// 메모리 레이아웃을 보장하기 위해 구조체 사용
typedef struct {
    int buffer[5];     // 인덱스 0 ~ 4
    int safe_value;    // 보호해야 할 중요 변수 (buffer 바로 뒤에 위치)
} AppData;

// 의도적인 버퍼 오버플로우 발생 함수
void corrupt_memory(AppData *data) 
{
    printf("데이터 처리 중...\n");
    
    // 버그: 인덱스 5에 접근 (buffer 범위를 초과하여 safe_value 영역 침범)
    for (int i = 0; i <= 5; i++) {
        data->buffer[i] = i * 10; 
    }
}

int main() 
{
    AppData app_data;
    app_data.safe_value = 999; // 초기값 설정
    
    printf("--- 디버깅 실습 시작 ---\n");
    printf("변경 전 safe_value: %d\n", app_data.safe_value);
    
    corrupt_memory(&app_data);
    
    // safe_value가 여전히 999일 것으로 기대하지만 50으로 변조됨
    printf("변경 후 safe_value: %d (기대값: 999)\n", app_data.safe_value); 
    printf("--- 프로그램 종료 ---\n");
    
    return 0;
}
