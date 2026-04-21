//- **입력:** 관리할 리소스 개수(예: 100개), 할당/해제 요청
//- **출력:** 할당된 인덱스 번호
//- **제약조건:** `uint8_t` 배열을 비트 단위로 쪼개서 사용 여부 마킹 (1bit = 1resource).

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	uint8_t* map;   // 실제 비트들을 담을 바이트 배열
	int total_bits; // 관리할 리소스 총 개수
	int array_size; // 배열의 크기 (바이트 단위)
} Bitmap;


Bitmap* create_bitmap(int num) {
	Bitmap* b = (Bitmap*)malloc(sizeof(Bitmap));
	if (!b) return NULL;

	b->total_bits = num;
	// 8로 나눈 뒤 나머지가 있으면 +1 (올림)
	b->array_size = (num + 7) / 8;

	// calloc을 사용하여 모든 비트를 0으로 초기화
	b->map = (uint8_t*)calloc(b->array_size, sizeof(uint8_t));
	if (!b->map) {
		free(b);
		return NULL;
	}
	return b;
}


int allocate_resource(Bitmap *b) {
	
	for (int i = 0; i < b->total_bits; i++) {
		int byte_idx = i / 8;
		int bit_pos = 7 - (i % 8); 

		// 해당 비트가 0인지 확인
		if (!(b->map[byte_idx] & (1 << bit_pos))) {
			b->map[byte_idx] |= (1 << bit_pos);
			return i; 
		}
	}
	return -1;
}

void free_resource(Bitmap* b, int idx) {
	if (idx < 0 || idx >= b->total_bits) return;

	int byte_idx = idx / 8;
	int bit_pos = 7 - (idx % 8);

	b->map[byte_idx] &= ~(1 << bit_pos);
}

void print_bitmap_visual(Bitmap* b) {
	printf("[Bitmap Visual]: ");
	for (int i = 0; i < b->total_bits; i++) {
		int byte_idx = i / 8;
		int bit_pos = 7 - (i % 8);

		if (b->map[byte_idx] & (1 << bit_pos)) printf("1");
		else printf("0");

		if ((i + 1) % 8 == 0) printf(" | "); // 8비트마다 공백
	}
	printf(" (Total: %d bits)\n", b->total_bits);
}

int main() {
	printf("=== Day 17: Bitmap Manager ===\n\n");

	// 1. 20개의 리소스를 관리하는 비트맵 생성 (3바이트 필요)
	Bitmap* bmp = create_bitmap(40);

	// 2. 할당 테스트
	allocate_resource(bmp); // idx 0
	allocate_resource(bmp); // idx 1
	allocate_resource(bmp); // idx 2
	int free_idx = allocate_resource(bmp); // idx 3 ... (반복해서 7까지 채움)
	int new_idx = 0;
	for (int i = 0; i < 15; i++)  new_idx = allocate_resource(bmp);

	print_bitmap_visual(bmp);

	// 3. 해제 테스트
	printf("\nFreeing index %d...\n", free_idx);
	free_resource(bmp, free_idx);
	printf(">> Index %d freed. (Byte %d, Bit %d cleared)\n", free_idx, 8/ new_idx, free_idx);

	print_bitmap_visual(bmp);

	// 4. 재할당 (빈 공간인 2번이 다시 할당되어야 함)
	printf("\nAllocating again (expecting index %d)...\n", free_idx);
	new_idx = allocate_resource(bmp);
	printf(">> Index: %d Allocated.\n", new_idx);

	print_bitmap_visual(bmp);

	// 정리
	free(bmp->map);
	free(bmp);

	return 0;
}


