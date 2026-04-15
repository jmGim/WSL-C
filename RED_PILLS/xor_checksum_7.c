#include <stdio.h>
#include <stdint.h>
#include <string.h>

// XOR 체크섬 계산 함수 (포인터 기반)
uint8_t calculate_xor_checksum(const uint8_t* data, size_t length) {
	uint8_t checksum = 0;
	const uint8_t* ptr = data; // 포인터 변수 생성

	for (size_t i = 0; i < length; i++) {
		checksum ^= *(ptr+i); // 현재 포인터가 가리키는 값 XOR
		//ptr++;            // 다음 주소로 포인터 이동
	}
	return checksum;
}

// 데이터와 체크섬 검증 함수 (포인터 기반)
int verify_xor_checksum(const uint8_t* data, size_t length, uint8_t received_checksum) {
	uint8_t calculated = calculate_xor_checksum(data, length);

	if (calculated == received_checksum) {
		return 1; // 성공
	}
	else {
		return 0; // 실패
	}
}

int main() {
	// 1. 데이터 준비
	uint8_t packet[7] = { 0x01, 0x04, 0x10, 0x20, 0x30, 0x40 };
	size_t packet_len = sizeof(packet);

	// 2. 송신측: 체크섬 계산 (포인터로 배열 시작 주소 전달)
	uint8_t tx_checksum = calculate_xor_checksum(packet, packet_len);
	printf("\n Receiving Normal Packet \n");

	for (int i = 0; i < packet_len; i++) {
		printf("0x%02x ", *(packet + i));
	}
	printf("\nCalculated Checksum: 0x%02X\n", tx_checksum);

	// 3. 수신측: 검증 (데이터가 깨지지 않았다고 가정)
	if (verify_xor_checksum(packet, packet_len, tx_checksum)) {
		printf("Verified Success!\n");
	}

	// 4. 검증 실패 케이스 (데이터 손상 가정)
	packet[6] = 0xEF; // 데이터 훼손
	printf("\n Receiving Corrupted Packet (Noise Injected)\n");
	for (int i = 0; i < packet_len; i++) {
		printf("0x%02x ", *(packet + i));
	}
	verify_xor_checksum(packet, packet_len, tx_checksum);
	printf("\nVerification Failed: result 0x%02X, Received 0x%02X\n", calculate_xor_checksum(packet, sizeof(packet)), tx_checksum);

	return 0;
}

