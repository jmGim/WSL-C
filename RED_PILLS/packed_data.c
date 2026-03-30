#include <stdio.h>
#include <string.h>
#define BIT_SHIFT_FUNCTION( reg, bit) (((unsigned int)(reg) >> bit) )
//((reg) | (1U << (pos)))

int main() {

	unsigned int inputReg = 0;
	unsigned int R = 0 , G = 0, B = 0;
	unsigned int mask_R = 0x1f, mask_G = 0x3f, mask_B = 0x1f;

	printf("\n=== Day 3: Packed Data Parsing (RGB565) ===\n\n");

	while (1) {

		printf("Input(16bit): ");
		scanf("%x", &inputReg);
	
		R |= (BIT_SHIFT_FUNCTION(inputReg, 11) & mask_R);
		G |= (BIT_SHIFT_FUNCTION(inputReg, 5) & mask_G);
		B |= (BIT_SHIFT_FUNCTION(inputReg, 0) & mask_B);

		printf(" [Raw Value] R: %u (0x%02x), G: %u (0x%02x), B: %u (0x%02x)\n", R, R, G, G, B, B);
		printf(" [8-bit Ext] R: %u ,\t G: %u ,\t B: %u \t\n", 
			(R << 3), (G << 2), (B << 3));
		printf("--------------------------------------------------\n\n");
		R = 0, G = 0, B = 0;
	}
}
