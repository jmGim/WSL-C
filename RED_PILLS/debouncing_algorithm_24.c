// - **Day 24. 디바운싱 (Debouncing) 알고리즘**
//     - **입력:** 노이즈가 섞인 0/1 입력 배열 (버튼 신호 모사)
//     - **출력:** 안정화된 출력 값
//     - **제약조건:** 연속된 N번의 샘플링이 동일할 때만 상태 변경.



#include <stdio.h>

int main() {
	// 버튼의 물리적 접점에서 읽어들인 가상의 Raw 데이터 배열 (노이즈 포함)
	int raw_inputs[] = { 0, 0, 1, 0, 1, 1, 1, 1, 1, 0 };
	int total_steps = sizeof(raw_inputs) / sizeof(raw_inputs[0]);

	// 디바운싱 처리를 위한 핵심 변수들
	int stable_state = 0;     // 최종적으로 필터링된 안정적인 출력 상태
	int counter = 0;          // 연속된 신호를 세는 카운터
	int required_samples = 3; // 상태를 변경하기 위해 필요한 연속 샘플 수 (디바운스 타임)

	printf("=== Day 24: Button Debouncing Logic ===\n");
	printf("Condition: %d consecutive samples required.\n\n", required_samples);
	printf("Step | Raw Input | Counter | Output (Stable)\n");
	printf("-----+-----------+---------+----------------\n");

	for (int i = 0; i < total_steps; i++) {
		int raw = raw_inputs[i];

		// 1. 현재 안정된 상태(stable_state)와 들어온 값(raw)이 다를 때
		if (raw != stable_state) {
			counter++; // 다르면 카운터를 1 증가시킴 (새로운 신호의 가능성)

			// 2. 카운터가 목표치(3회)에 도달했는지 확인
			if (counter >= required_samples) {
				// 3번 연속으로 같은 값이 들어왔으므로 노이즈가 아닌 '진짜 신호'로 인정!
				printf("  >> [State Changed] to %d\n", raw);
				stable_state = raw; // 출력 상태를 새로운 값으로 업데이트
				counter = 0;        // 상태가 바뀌었으므로 카운터는 다시 0으로 초기화
			}
		}
		// 3. 들어온 값(raw)이 이미 안정된 상태와 같을 때
		else {
			counter = 0; // 튀는 노이즈가 끝났거나 정상 상태이므로 카운터를 즉시 리셋
		}

		// 실행 결과를 동일하게 재현하기 위한 주석(Annotation) 처리
		const char* annotation = "";
		if (i == 2) annotation = "<-- 노이즈 발생 (카운트 시작)";
		if (i == 3) annotation = "<-- 다시 0 복귀 (카운트 리셋!)";
		if (i == 4) annotation = "<-- 진신호 시작";
		if (i == 6) annotation = "<-- 3회 연속 성공으로 상태 변경";
		if (i == 9) annotation = "<-- 노이즈 무시";

		// 현재 스텝의 상태 출력
		printf(" %3d |     %d     |    %d    |       %d  %s\n",
			i + 1, raw, counter, stable_state, annotation);
	}

	return 0;
}
