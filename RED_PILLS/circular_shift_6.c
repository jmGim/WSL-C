#include <stdio.h>
#include <string.h>  // built-in-funcion>
#define INT_BITS 32

void print_in_binary(unsigned int n);
unsigned int rotate_left(unsigned int value, int shift);
unsigned int rotate_right(unsigned int value, int shift);
int main() {

	unsigned int inputReg = 0xf0000000;
	short while_cnt = 1;
	char command[10];
	int nbit = 0;
	
	printf("\n===  Day 6: Circular Shift (Rotate) ===\n");
	while (1) {
		printf(" (LEFT, RIGHT) : ");
		scanf("%s", command);
		printf(" nbit : ");
		scanf("%d", &nbit);
		printf("\n");
		if (strcmp(command, "LEFT") == 0) {
			inputReg = rotate_left(inputReg, nbit);
		}
		else if (strcmp(command, "RIGHT") == 0) {
			inputReg = rotate_right(inputReg, nbit);
		}

		printf("[%s %d]  \n", command, nbit);
		printf(" Hex : 0x%08x\n", inputReg);
		print_in_binary(inputReg);
		printf("\n\n");
		
	}
	return 0;
}

unsigned int rotate_left(unsigned int value, int shift) {
	shift %= INT_BITS;
	return (value << shift) | (value >> (INT_BITS - shift));
}

unsigned int rotate_right(unsigned int value, int shift) {
	shift %= INT_BITS;
	return (value >> shift) | (value  << (INT_BITS - shift));
}


void print_in_binary(unsigned int n) {
	printf("Bin : ");
	for (int i = 31; i >= 0; i--) {
		printf("%d", (n >> i) & 1);
		if (i % 4 == 0 && i != 0) {
			printf(" ");

		}
	}
}

