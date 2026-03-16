#include <stdio.h>

int main(){

	char originChar[30];
	char changeChar[30];

	int changeCount = 0;

	printf("문장 입력 : ");
	fgets(originChar, sizeof(originChar), stdin);

	for (int i = 0; i < sizeof(originChar); i++) {
		/*if ('A' <= originChar[i]  && originChar[i] <= 'Z') {
			changeChar[i] = originChar[i] + 32;
			changeCount += 1;
		} else {
			changeChar[i] = originChar[i];
		}*/

		changeChar[i] = ((originChar[i] >= 'A') && originChar[i] <= 'Z') ? (changeCount += 1, originChar[i] + 32) : originChar[i]; 	}

	printf("바뀐 문장 : %s\n", changeChar);
	printf("바뀐 문장 수 : %d\n", changeCount);

	return 0;
}
