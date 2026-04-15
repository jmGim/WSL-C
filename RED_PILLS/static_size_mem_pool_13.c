// - **입력:** 할당 요청
// - **출력:** 할당된 메모리 블록 주소 (실패 시 NULL)
// - **제약조건:** 런타임에 `malloc` 사용 금지. 미리 잡아둔 큰 배열 안에서 청크를 쪼개 줄 것.
// - **2. 구현 목표**
//    - **블록 크기:** 32 Bytes
//    - **블록 개수:** 10개
//    - **기능:** 초기화(`init`), 할당(`alloc`), 해제(`free`)

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// 설정: 블록 크기와 개수
#define BLOCK_SIZE  32
#define POOL_SIZE   10

// 메모리 블록 구조체 (Free List 관리를 위한 연결 리스트 노드)
// [핵심 개념] 할당되지 않은 빈 메모리 블록의 앞 8바이트(64비트 기준)를 포인터로 재사용합니다.
// 메모리가 할당되어 사용 중일 때는 이 포인터는 덮어씌워져 유저 데이터로 쓰입니다.
typedef struct Block {
	struct Block* next;
} Block;

// 메모리 풀 컨텍스트
typedef struct {
	// 실제 메모리 공간 (바이트 배열)
	// 1차원 바이트 배열로 미리 필요한 공간(32바이트 * 10개 = 320바이트)을 싹 잡아둡니다.
	uint8_t memory_area[POOL_SIZE * BLOCK_SIZE];

	// 현재 사용 가능한 첫 번째 빈 블록을 가리키는 포인터
	Block* free_list;

	// 디버깅용: 현재 사용 중인 블록 수
	int used_count;
} MemoryPool;

// 전역 풀 인스턴스 (BSS 영역에 할당됨)
MemoryPool my_pool;

// 1. 초기화: 모든 메모리를 쪼개서 연결 리스트로 연결
void pool_init(MemoryPool* pool) {
	pool->used_count = 0;

	// 첫 번째 블록의 주소를 free_list의 헤드(Head)로 설정합니다.
	pool->free_list = (Block*)&pool->memory_area[0];

	Block* current = pool->free_list;

	// 전체 풀 사이즈(10개)만큼 반복하며 각 블록을 다음 블록과 연결합니다.
	for (int i = 0; i < POOL_SIZE - 1; i++) {
		// 다음 블록의 시작 주소 = 현재 바이트 배열 시작점 + (인덱스 * 블록 크기)
		// (Block*) 캐스팅을 통해 순수한 바이트 주소를 Block 구조체 포인터로 변환합니다.
		Block* next_block = (Block*)&pool->memory_area[(i + 1) * BLOCK_SIZE];

		current->next = next_block; // 현재 블록이 다음 빈 블록을 가리키게 함
		current = next_block;       // 다음 블록으로 이동
	}

	// 마지막 블록의 next는 NULL로 설정하여 끝을 알립니다.
	current->next = NULL;

	printf("[Init] Memory Pool Initialized (%d blocks of %d bytes)\n", POOL_SIZE, BLOCK_SIZE);
	printf("[Init] Memory Pool Initialized (%d blocks of %d bytes)\n", POOL_SIZE, BLOCK_SIZE);
}

// 2. 할당: Free List의 헤드(Head)를 떼어줌 (Pop)
void* pool_alloc(MemoryPool* pool) {
	// 빈 블록이 없으면(Out of Memory) NULL 반환
	if (pool->free_list == NULL) {
		printf("Error: Memory pool is empty!\n");
		return NULL;
	}

	// 1. 반환해줄 블록(현재 헤드)을 임시 저장
	Block* allocated_block = pool->free_list;

	// 2. 헤드 포인터를 다음 빈 블록으로 이동 (리스트에서 빼내기)
	pool->free_list = allocated_block->next;

	// 3. 디버깅용 카운트 증가
	pool->used_count++;

	// 4. void* 로 캐스팅하여 반환 (유저가 어떤 타입으로든 쓸 수 있게 함)
	return (void*)allocated_block;
}

// 3. 해제: 반환된 블록을 Free List의 헤드에 다시 붙임 (Push)
void pool_free(MemoryPool* pool, void* ptr) {
	// 잘못된 포인터 방어 코드
	if (ptr == NULL) return;

	// 1. 반환받은 메모리 주소를 다시 Block 포인터로 캐스팅 (비어있으니 다시 next를 쓸 수 있음)
	Block* block_to_free = (Block*)ptr;

	// 2. LIFO(Stack) 방식으로, 반환된 블록이 기존의 헤드를 가리키게 함
	block_to_free->next = pool->free_list;

	// 3. 이제 헤드는 방금 반환된 블록이 됨
	pool->free_list = block_to_free;

	// 4. 카운트 감소
	pool->used_count--;
}

// 테스트 코드
int main() {
	pool_init(&my_pool);

	// 3개 할당
	void* p1 = pool_alloc(&my_pool);
	void* p2 = pool_alloc(&my_pool);
	void* p3 = pool_alloc(&my_pool);

	printf("Allocated: %p, %p, %p\n", p1, p2, p3);
	printf("Used Blocks: %d\n", my_pool.used_count);

	// 1개 해제 (p2)
	printf("Freeing %p...\n", p2);
	pool_free(&my_pool, p2); // 이제 p2가 free_list의 head가 됨
	printf("Used Blocks: %d\n", my_pool.used_count);

	// 다시 1개 할당 (p2와 같은 주소가 나와야 함 - LIFO 특성)
	void* p4 = pool_alloc(&my_pool);
	printf("Re-allocated: %p (Should be same as old p2)\n", p4);
	printf("Used Blocks: %d\n", my_pool.used_count);

	return 0;
}

