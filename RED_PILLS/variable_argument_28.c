// - **입력:** 포맷 스트링 `"%d %s"`, 가변 인자
// - **출력:** 포맷팅된 문자열 출력
// - **제약조건:** `<stdarg.h>` 사용, `%d`, `%x`, `%s`만 지원.  …


#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

//void my_printf(const char * format...);


void my_printf(const char* format, ...) {
	va_list ap;
	va_start(ap, format);

	for (const char* p = format; *p != '\0'; p++) {
		if (*p == '%') {
			p++; // % 다음 문자로 이동
			switch (*p) {
			case 'd': // 정수
				printf("%d", va_arg(ap, int));
				break;
			case 'x': // 정수
				printf("%x", va_arg(ap, unsigned int));
				break;
			case 'f': // 실수 (float은 double로 승격)
				printf("%f", va_arg(ap, double));
				break;
			case 'c': // 문자 (char는 int로 승격)
				printf("%c", va_arg(ap, int));
				break;
			case 's': // 문자열
				printf("%s", va_arg(ap, char*));
				break;
			case '%': // %% 처리
				putchar('%');
				break;
			default:
				putchar(*p);
			}
		}
		else {
			putchar(*p); // 일반 문자 출력
		}
	}
	va_end(ap);
	printf("\n");
}


int main() {
	printf("=== Day 28: Custom printf Implementation ===\n\n");

	// Test 1: 정수와 문자열
	my_printf("MyPrint: %d %s\n", 10, "test");

	// Test 2: 16진수와 음수
	my_printf("Hex: 0x%x, Negative: %d\n", 255, -12345);

	// Test 3: 여러 인자 혼합
	my_printf("Result: %d + %d = %d\n", 10, 20, 30);

	return 0;
}
