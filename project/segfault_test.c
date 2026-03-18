#include <stdio.h>

// 값을 업데이트하는 함수 (에러 발생 지점)
void update_value(int *ptr) 
{
    printf("update_value() 진입: 포인터에 값 쓰기 시도...\n");
    *ptr = 100; // ptr이 NULL이므로 여기서 Segmentation Fault 발생
}

// 데이터를 처리하는 중간 함수
void process_data(int *data_ptr) 
{
    printf("process_data() 진입: 데이터 처리 중...\n");
    update_value(data_ptr);
}

int main() 
{
    int *my_ptr = NULL; // 널 포인터 선언 (할당 누락 가정)
    
    printf("--- 디버깅 실습 프로그램 시작 ---\n");
    
    // 메모리 할당(malloc) 없이 바로 함수로 포인터 전달
    process_data(my_ptr); 
    
    printf("--- 프로그램 정상 종료 ---\n");
    return 0;
}
