// - **입력:** 바이트 배열
// - **출력:** 32비트 CRC 체크섬
// - **제약조건:** 비트 단위 계산 방식 구현 후, 테이블 기반 방식으로 최적화 비교.
// - **실행결과:**  ethernet checksum?, can checksum

// Cyclic Redundancy Check
// is based on the following generator polynomial: g(x) = x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 + x5 + x4 + x2 + x + 1.
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define CRC32_POLY 0xEDB88320u
#define CRC32_INIT 0xFFFFFFFFu
#define CRC32_XOROUT 0xFFFFFFFFu

uint32_t crc32_bitwise(const uint8_t *data, size_t len)
{
    uint32_t crc = CRC32_INIT;

    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];

        for (int bit = 0; bit < 8; bit++) {
            if (crc & 1u) {
                crc = (crc >> 1) ^ CRC32_POLY;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc ^ CRC32_XOROUT;
}

void crc32_generate_table(uint32_t table[256])
{
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t crc = i;

        for (int bit = 0; bit < 8; bit++) {
            if (crc & 1u) {
                crc = (crc >> 1) ^ CRC32_POLY;
            } else {
                crc >>= 1;
            }
        }

        table[i] = crc;
    }
}

uint32_t crc32_table_based(const uint8_t *data, size_t len)
{
    uint32_t table[256];
    uint32_t crc = CRC32_INIT;

    crc32_generate_table(table);

    for (size_t i = 0; i < len; i++) {
        uint8_t index = (uint8_t)((crc ^ data[i]) & 0xFFu);
        crc = (crc >> 8) ^ table[index];
    }

    return crc ^ CRC32_XOROUT;
}

int main(void)
{
    const uint8_t input[] = "123456789";
    size_t len = sizeof(input) - 1;

    uint32_t crc_bitwise = crc32_bitwise(input, len);
    uint32_t crc_table = crc32_table_based(input, len);

    printf("=== Day 27: CRC-32 Implementation ===\n");
    printf("Input Data: \"%s\"\n\n", input);

    printf("[Bit-wise] CRC: 0x%08X\n", crc_bitwise);
    printf("[Table-based] CRC: 0x%08X\n\n", crc_table);

    if (crc_bitwise == 0xCBF43926u && crc_table == 0xCBF43926u) {
        printf(">> Verification Success! (Matches Standard)\n");
    } else {
        printf(">> Verification Failed!\n");
    }

    return 0;
}

