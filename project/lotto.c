#include <stdio.h>

int main() { 
	int lotto[6];
	int *p = lotto;

	int i = 0;
	int flag = 0;
	while(i < 6) {
		printf("번호 입력 : ");
		scanf("%d", (p+i)); 
		for (int j = 0; j < i; j++ ){
			if (*(p+i) == *(p+j) ) {
				printf("같은 번호가 있습니다!\n");
				flag = 1;
				break;
			} else flag = 0; 
		} if (flag != 1) i++;
		
	}
	printf("p size : %ld\n", sizeof(p));
	printf("lotto size : %ld\n ", sizeof(lotto));
	printf("로또 번호 : ");
	for (int j = 0; j < 6; j++) {
		printf(" %d ", *(lotto+j));
	}
}
