#include <stdio.h>
#include <string.h>

unsigned int bit_set(unsigned int reg, int pos) {
	return reg | ((unsigned int)1 << pos);
}

unsigned int bit_clear(unsigned int reg, int pos) {
	return reg & ~((unsigned int)1 << pos);
}

unsigned int bit_toggle(unsigned int reg, int pos) {
	return reg ^ ((unsigned int)1 << pos);
}

int bit_check(unsigned int reg, int pos) {
	return (reg << pos) & (unsigned int)1;
}

void print_in_binary(unsigned int n) {
	for (int i = 31; i >= 0; i--) {
		printf("%d", (n >> i) & 1);
		if (i % 8 == 0 && i != 0) {
			printf(" ");
		} 
		
	}
}
int main() {
	unsigned int InputReg = 0;
	int bitPos = 0;
	char command[10];

	unsigned int OutputReg = InputReg;

	while (1) {

	
		printf("InputRegister: (ex.0x01) ");
		scanf("%x", &InputReg);

		printf("Position: ");
		scanf("%d", &bitPos);

		printf("Command: ");
		scanf("%s", command);
	
		if (strcmp(command, "QUIT") == 0) {
			printf("종료\n");
			break;
		}
		
		if (bitPos < 0 || bitPos > 31) {
			printf("Error: bitPos 범위 : 0 ~ 31 \n");
		}

		if (strcmp(command, "SET") == 0) {
			OutputReg = bit_set(InputReg, bitPos);
		}
		else if (strcmp(command, "CLEAR") == 0) {
			OutputReg = bit_clear(InputReg, bitPos);
		}
		else if (strcmp(command, "TOGGLE") == 0) {
			OutputReg = bit_toggle(InputReg, bitPos);
		}
		else if (strcmp(command, "CHECK") == 0) {
			printf("InputRegister[%d] = %x\n", bitPos, bit_check(InputReg, bitPos));
			return 0;
		}
		else {
			printf("Error: 잘못된 명령어 기입\n");
		}

		printf("Result: 0x%08X\n", OutputReg);
		printf("(Binary: "); print_in_binary(OutputReg); printf(")\n\n");
	}
	return 0;
}
