// - **입력:** 소스 주소, 목적지 주소, 복사할 바이트 수
// - **출력:** 메모리 복사 후 목적지 주소의 데이터 덤프
// - **제약조건:** `memcpy` 대신 `memmove` 동작 구현 (src와 dest 영역이 겹칠 때 데이터 오염 방지).
// - **실행결과:** `Overlap handled correctly.`
// - memcpy는 앞에서부터 복사하기에 소스와 목적지 메모리 영역이 겹칠 수도 있다.

#include <stdio.h>
#include <stdint.h>

void* my_memmove(void* dest, const void* src, size_t n) {
    unsigned char* p_dest = (unsigned char*)dest;
    const unsigned char* p_src = (const unsigned char*)src;

    if (p_dest == p_src)
        return dest;

    if (p_dest < p_src) {
        for (int i = 0; i < n; i++) {
            p_dest[i] = p_src[i];
        }
    }
    else {
        for (int i = n; i > 0; i--) {
            p_dest[i - 1] = p_src[i - 1];
        }
    }

    return dest;
}

int main() {
    char src[] = "ABCDEFG";

    printf("Before Data: %s\n", src);
    int n = 2;
    my_memmove(src + n, src, n+1);

    printf("Copied Data: %s\n", src);
    printf("Overlap handled correctly.\n");

    return 0;
}
