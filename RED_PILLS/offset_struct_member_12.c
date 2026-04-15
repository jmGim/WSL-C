// - **입력:** 구조체 타입명, 멤버 변수명
// - **출력:** 구조체 시작 주소로부터 해당 멤버까지의 바이트 거리
// - **제약조건:** `<stddef.h>` 표준 offsetof 사용 (비교용)  ⇒ 사용 금지. **0번지 주소 캐스팅 기법 활용.**
// - **실행결과:**


#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define MY_OFFSETOF(type, member) ((size_t)&(((type *)0)->member))


// 테스트를 위한 구조체 (패딩이 발생하는 구조)
#pragma pack(push, 1) 
typedef struct {
	
	char a;      // 1 byte
	// (padding 3 bytes) - 4바이트 정렬을 위해 컴파일러가 넣음
	int b;       // 4 bytes
	double c;    // 8 
	
} Sample;
#pragma pack(pop)

typedef struct {
	const char* member_name;
	size_t offset;
} OffsetMap;

int main() {
	printf("=== Day 12: offsetof Implementation ===\n");

	Sample s1;
	OffsetMap map[] = {
		{"a", MY_OFFSETOF(Sample, a)},
		{"b", MY_OFFSETOF(Sample, b)},
		{"c", MY_OFFSETOF(Sample, c)},
	};
	int map_size = sizeof(map) / sizeof(map[0]);


	// %zu는 size_t 타입(배열 크기, 문자열 길이)을 출력하는 서식 지정자
	printf("Struct size: %zu bytes \n", sizeof(Sample));

		
	printf("[Standard] Offset of '%c' : %zu\n", 'a', offsetof(Sample, a));
	printf("[Standard] Offset of '%c' : %zu\n", 'b', offsetof(Sample, b));
	printf("[Standard] Offset of '%c' : %zu\n", 'c', offsetof(Sample, c));
	printf("\n\n");

	for (int i = 0; i < map_size; i++) {
		printf("[Custom] Offset of '%s' : %zu\n", map[i].member_name, map[i].offset);
		//break;
	}

	printf(">> Success! Implementation is correct.");

	return 0;
}
