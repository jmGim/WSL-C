#include <stdio.h> 

int main() {
	
	char* inputWord;
	
	int i = 0, wordLength = 0;
	while(1) {
		if (scanf("%s", inputWord) == EOF) {			
			printf("^Z\n");
			break;
		}

		//if (inputWord == "^Z") break;
			
		i = 0;
		while(inputWord[i] != '\0'){	
			//if (inputWord == "^Z" || inputWord == -1) break;
			i++;
		}
		
		if (wordLength < i) wordLength = i;

			
	}
	printf("가장 긴 단어의 길이 : %d\n", wordLength);
	return 0;
}
