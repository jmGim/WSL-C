#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAX_WORD_LENGTH 30
int compare(const void *a, const void  *b);

int main() {
	int n = 3;
	
	char word[n][MAX_WORD_LENGTH];
	printf("세 단어 입력 : ");
	for (int i = 0; i < n; i++) {
		scanf("%s", word[i]);
	}

	qsort(word, n, sizeof(word[0]), compare);

	for (int i = 0; i < n; i++) {
		printf(" %2s ", word[i]); 
	}
	return 0;
	
}

int compare(const void *a, const void *b) {
    //char ch1 = *(char *)a;
    //char ch2 = *(char *)b;
	return strcmp((const char *)a, (const char *)b);
    //if (ch1 < ch2) return -1;
    //if (ch1 > ch2) return 1;
    //return 0;
    // return (*(char*)a - *(char*)b); // 간결한 방식
}
