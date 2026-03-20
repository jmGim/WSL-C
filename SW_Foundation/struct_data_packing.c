#include <stdio.h>

#pragma pack(push, 1)
struct PackedPacket1 {
	unsigned char id;       // 1
	unsigned int timestamp; // 4
	unsigned short data;    // 2
	unsigned char checksum; // 1
} ;
#pragma pack(pop)


struct PackedPacket2 {
	unsigned char id;       // 1
	unsigned int timestamp; // 4
	unsigned short data;    // 2
	unsigned char checksum; // 1
};


int main() {

	struct PackedPacket1 s1 = { '1', 1, 11, 111 };
	struct PackedPacket2 s2 = { '2', 2, 22, 222 };
	printf("Packet1 구조체의 크기 : %ld바이트\n", sizeof(s1));
	printf("Packet2 구조체의 크기 : %ld바이트\n", sizeof(s2));
	printf("Packet1의 id주소 %p와 timestamp 주소 %p의 차이 = %ld\n", &s1.id, &s1.timestamp, (char *)(&s1.timestamp) - (char *)(&s1.id));
	printf("Packet2의 id주소 %p와 timestamp 주소 %p의차이 = %ld\n", &s2.id, &s2.timestamp, (char *)(&s2.timestamp) - (char *)(&s2.id));

	return 0;
}
