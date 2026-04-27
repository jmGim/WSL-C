// **Day 25. 이동 평균 필터 (Moving Average)**
//    - **입력:** 센서 노이즈 데이터 스트림
//    - **출력:** 필터링된 값
//    - **제약조건:** 최근 N개의 데이터를 저장하는 윈도우 버퍼 사용, 매번 합계 다시 계산하지 말고 최적화(Sliding Window).
#include <stdio.h>

#define BUFFER_SIZE 5

typedef struct  {
	float buffer[BUFFER_SIZE];
	int sum;   
	int count; 
	int index;
	
} mvFilter;


void initFilter(mvFilter* filter) {
	for (int i = 0; i < BUFFER_SIZE; i++) {
		filter->buffer[i] = 0.0f; // 버퍼 0으로 초기화
	}
	filter->index = 0;
	filter->count = 0;
	filter->sum = 0.0f;
}

float updateFilter(mvFilter* filter, float new_value) {
	filter->sum -= filter->buffer[filter->index];
	filter->sum += new_value;
	filter->buffer[filter->index] = new_value;
	filter->index = (filter->index + 1) % BUFFER_SIZE;

	if (filter->count < BUFFER_SIZE) filter->count++;

	return (float)filter->sum / filter->count;
}

int main() {
	// 입력될 가상의 센서 데이터 스트림
	float raw_inputs[] = { 20.0, 22.0, 18.0, 25.0, 15.0, 20.0, 21.0, 19.0, 20.5, 20.0 };
	int total_steps = sizeof(raw_inputs) / sizeof(raw_inputs[0]);

	// 구조체 변수 선언 및 초기화
	mvFilter filter;
	initFilter(&filter);

	printf("=== Day 25: Moving Average Filter (Sliding Window) ===\n");
	printf("Window Size: %d\n\n", BUFFER_SIZE);
	printf("Step | Raw Input | Filtered Output\n");
	printf("-----+-----------+----------------\n");

	for (int i = 0; i < total_steps; i++) {
		float raw = raw_inputs[i];

		// 필터 업데이트 및 결과 수신
		float filtered = updateFilter(&filter, raw);
		printf(" %3d |    %4.1f   |       %4.1f", i + 1, raw, filtered);

	
		// 단계별 주석(설명) 출력
    	if (i == 0) printf("  (1개 평균)\n");
    	else if (i == 1) printf("  (2개 평균)\n");
    	else if (i == 2) printf("  (3개 평균: 20+22+18 / 3)\n");
    	else if (i == 4) printf("  (5개 꽉 참)\n");
    	else if (i == 5) printf("  (20.0이 들어오고, 맨 처음 20.0이 빠짐)\n");
    	else if (i == 6) printf("  (21.0이 들어오고, 22.0이 빠짐 -> 평균 하락)\n");
    	else printf("\n");
	}
	return 0;
}

