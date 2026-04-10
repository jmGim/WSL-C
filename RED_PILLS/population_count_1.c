#include <stdio.h>


void naive_function(unsigned int reg);
void kernighan_function(unsigned int reg);
void swar_function(unsigned int reg);
void built_in_function(unsigned int reg);


int main() {

	unsigned int inputReg = 0;
	short while_cnt = 1;
	printf("\n===  Day 5: Population Count (Counting Set Bits) ===\n");

	while (1) {
		printf("Case %d:\n", while_cnt);

		printf(" Input : 0x");
		scanf("%x", &inputReg);
		
		naive_function(inputReg);
		kernighan_function(inputReg);
		swar_function(inputReg);
		built_in_function(inputReg);
		while_cnt++;
		printf("---------------------------------------------------\n");
	}
}



void naive_function(unsigned int reg) {
	short count = 0;
	
	for (int i = 31; i >= 0; i--) {
		if ((reg >> i) & 1) {
			count++;
		}
	}
	printf("  [Naive]     : %d\n", count);
	
}


void kernighan_function(unsigned int reg) {
	short count = 0;

	while (reg > 0) {
		// Clear the least significant set bit
		reg &= (reg - 1);
		count++;
	}
	printf("  [kernighan] : %d (Recommended Logic)\n", count);

}

void swar_function(unsigned int reg) {
	//short count = 0;
	reg = (reg & 0x55555555) + ((reg >> 1) & 0x55555555);
	reg = (reg & 0x33333333) + ((reg >> 2) & 0x33333333);
	reg = (reg & 0x0f0f0f0f) + ((reg >> 4) & 0x0f0f0f0f);
	reg = (reg & 0x00ff00ff) + ((reg >> 8) & 0x00ff00ff);
	reg = (reg & 0x0000ffff) + ((reg >> 16) & 0x0000ffff);

	printf("  [SWAR]      : %d (Strict Loop-free)\n", reg);

}

void built_in_function(unsigned int reg) {
	int count = __builtin_popcount(reg);
	printf("  [Built-in]  : %d\n", count);

}
