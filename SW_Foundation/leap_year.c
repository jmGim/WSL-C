#include <stdio.h>

int main() {
	int leapYear[4] = {2020, 1900, 2000, 2021};
	char resLeapYear[4] = {}; 
	for (int i = 0; i < 4; i++) {
		/*
		if (leapYear[i] % 400 == 0) {
			resLeapYear[i] = 'O';
			continue;

		} else if(leapYear[i] % 100 == 0) {  
			resLeapYear[i] = 'X';
			continue;
		} else if (leapYear[i] % 4 == 0) { 
			resLeapYear[i] = 'O';
		} else resLeapYear[i] = 'X';

		*/
		resLeapYear[i] = (leapYear[i] % 400 == 0) ? 'O' : (leapYear[i] % 100 == 0) ? 'X' : (leapYear[i] % 4 == 0 ) ? 'O' : 'X';   	
	}

	for (int i = 0; i < 4; i++) {

		printf("%d년 : %c\n", leapYear[i], resLeapYear[i]);
	}
	return 0;

}
