 
#include <stdio.h>  
#include <string.h>
#include <stdlib.h> 
 
#define MAX_LINE 1024
 
 int main() { 
      FILE *fp1, *fp2, *fp3;
      char line1[MAX_LINE];
      char line2[MAX_LINE];
     int found;
     char a_txt[10][50] = { "dog", "tiger", "horse", "monkey", "lion", "koala",     "giraffe", "owl" };
      char b_txt[15][50] = {"lion", "elephant", "pear", "dog", "tiger", "apple",     "kangaroo", "orange", "bear", "owl"};
 
      // 1. 파일 쓰기: file1.txt, file2.txt 생성
     fp1 = fopen("a.txt", "w");
     fp2 = fopen("b.txt", "w");

     if (fp1 == NULL || fp2 == NULL) {
         perror("파일 열기 실패");
         return -1;
     }
      // 개행문자(\n)를 사용하여 문장 입력
      for (int i = 0; i < (sizeof(a_txt) / sizeof(a_txt[0]) ); i++){
          fprintf(fp1, "%s\n", a_txt[i] );
      }
 
 
      for (int i = 0; i < ( sizeof(b_txt) / sizeof(b_txt[0])); i++){
          fprintf(fp2, "%s\n", b_txt[i] );
      }
 
 
      fclose(fp1);
      fclose(fp2);
      printf("a.txt와 b.txt가 생성되었습니다.\n");
 
      // 2. 파일 비교 및 결과 저장 (fp3)
      fp1 = fopen("a.txt", "r");
      fp3 = fopen("c.txt", "w"); // 결과 파일
 
      if (fp1 == NULL || fp3 == NULL) {
          perror("파일 열기 실패");
          return -1;
      }
 
      printf("\n[a.txt에만 있는 단어]\n");
      // a의 각 줄을 읽음
      while (fgets(line1, MAX_LINE, fp1) != NULL) {
          found = 0;
          fp2 = fopen("b.txt", "r"); // 비교할 때마다 file2를 부터 읽음
 
          // b의 각 줄을 읽어 비교
          while (fgets(line2, MAX_LINE, fp2) != NULL) {
              if (strcmp(line1, line2) == 0) {
                  found = 1;
                  break;
              }
          }
          fclose(fp2);
 
          // b에 없는 단어인 경우, 화면과 diff.txt에 출력
          if (!found) {
              printf("%s", line1);
              fputs(line1, fp3);
          }
      }
      printf("\n결과가 c.txt에 저장되었습니다.\n");
      fclose(fp1);
      fclose(fp3);
 
      return 0;
}
