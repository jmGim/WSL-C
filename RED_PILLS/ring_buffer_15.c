// - **입력:** 데이터 Push/Pop 요청
// - **출력:** 버퍼 상태 (Full/Empty), 꺼낸 데이터
// - **제약조건:** 배열로 구현, Head/Tail 인덱스 관리, 오버플로우 방지 로직.
// - **실행결과:**



#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// 버퍼의 전체 크기 정의
#define BUFFER_SIZE 8

// 링 버퍼 구조체 정의
typedef struct {
	uint8_t buffer[BUFFER_SIZE]; // 실제 데이터를 저장할 8바이트 배열
	int head;                    // 데이터를 쓸(Write) 위치를 가리키는 인덱스
	int tail;                    // 데이터를 읽을(Read) 위치를 가리키는 인덱스
} RingBuffer;

// 1. 링 버퍼 초기화 함수
void rb_init(RingBuffer* rb) {
	rb->head = 0; // 초기 쓸 위치 0
	rb->tail = 0; // 초기 읽을 위치 0
}

// 2. 링 버퍼 full 검사
// // 포화(Full) 상태 검사
	// 만약 '다음 쓸 위치'가 '현재 읽을 위치(tail)'와 같다면, 버퍼가 가득 찬 것입니다.
	// (주의: 버퍼 크기가 8이어도, Full과 Empty를 구분하기 위해 최대 7개까지만 저장합니다.)
bool rb_is_full(RingBuffer* rb) {
	int next_head = (rb->head + 1) % BUFFER_SIZE;

	return (next_head == rb->tail);
}

// 3. 링 버퍼 empty 검사 

bool rb_is_empty(RingBuffer* rb) {
	return (rb->head == rb->tail);
}


// 2-2. 링 버퍼 쓰기 (데이터 삽입) 함수
bool rb_put(RingBuffer* rb, uint8_t data) {
	// 다음 쓸 위치(next_head)를 계산합니다.
	// '%' (모듈로) 연산을 사용하면 인덱스가 배열 끝(7)에 도달했을 때 다시 0으로 돌아옵니다. (Wrap-around)
	if (rb_is_full(rb)) {
		return false; // 저장 실패
	}

	rb->buffer[rb->head] = data;
	rb->head = (rb->head + 1) % BUFFER_SIZE; // next_head를 따로 저장할 필요 없이 바로 적용

	return true; // 저장 성공
}

// 3. 링 버퍼 읽기 (데이터 추출) 함수
bool rb_get(RingBuffer* rb, uint8_t* data) {
	// 빈(Empty) 상태 검사
	if (rb_is_empty(rb)) {
		return false; // 읽기 실패 (데이터 없음 에러 방어)
	}

	*data = rb->buffer[rb->tail];
	rb->tail = (rb->tail + 1) % BUFFER_SIZE;

	return true; // 읽기 성공
}

// ---- 테스트 코드 ----
int main() {
	RingBuffer uart_rx_buf;
	uint8_t temp;

	rb_init(&uart_rx_buf);

	printf("--- Phase 1: Filling Buffer ---\n");
	// 버퍼 사이즈가 8이므로, 한 칸 비우면 최대 7개 저장 가능
	for (int i = 1; i <= 10; i++) {
		if (rb_put(&uart_rx_buf, i)) {
			printf("Put: %d (Head: %d, Tail: %d)\n", i, uart_rx_buf.head, uart_rx_buf.tail);
		}
		else {
			printf("Fail to Put: %d (Buffer Full!)\n", i);
		}
	}

	printf("\n--- Phase 2: Reading Buffer ---\n");
	// 3개만 읽어봄
	for (int i = 0; i < 10; i++) {
		if (rb_get(&uart_rx_buf, &temp)) {
			printf("Get: %d (Head: %d, Tail: %d)\n", temp, uart_rx_buf.head, uart_rx_buf.tail);
		}
	}

	printf("\n--- Phase 3: Writing again (Wrap around) ---\n");
	// 읽어서 공간이 생겼으므로 다시 쓰기 가능 (인덱스가 0으로 돌아가는지 확인)
	if (rb_put(&uart_rx_buf, 99)) {
		printf("Put: 99 (Head: %d, Tail: %d)\n", uart_rx_buf.head, uart_rx_buf.tail);
	}

	return 0;
}
