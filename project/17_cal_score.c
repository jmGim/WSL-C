#include <stdio.h>
#define STU_NUM 5
#define SUB_NUM 3

int advanced_selection_sort(int* arr, int size);
   
struct student       // 학생 구조체 선언
{
	int id;          // 학번
	char name[20];   // 이름
	int kor;    
    int eng;
    int math;
    
    double average;
    char grade;

};

int main(void)
{
	struct student stu[5] = { 
                  { 315, "홍길동", 80, 75, 90, 0.0, 'F' },   // 구조체 변수 선언과 초기화
				   { 316, "이순신", 88, 92, 100, 0.0, 'F' },
				   { 317, "서하윤", 95, 99, 98, 0.0, 'F' },
				   { 318, "유관순", 84, 70, 72, 0.0, 'F' },
				   { 319, "박신혜", 60, 65, 40, 0.0, 'F' },
	
    };
    struct student max;					   // 최고 학점을 저장할 구조체 변수
    
    
    int p_average[5] = {stu[0].average, stu[1].average, stu[2].average, stu[3].average, stu[4].average};
    
	double max_average = stu[0].average;
   
    for( int i = 0; i < STU_NUM; i++){
        stu[i].average = (double)(stu[i].kor + stu[i].eng + stu[i].math) / 3;
        stu[i].grade = (stu[i].average >= 90) ? 'A' : (stu[i].average >= 80) ? 'B' : (stu[i].average >= 70) ? 'C' : 'F';
    }
       
	advanced_selection_sort(p_average, STU_NUM);

    for (int i = 0; i < 5; i++){
        printf("%d %s %4d %4d %4d %4.1f %c\n", stu[i].id, stu[i].name, stu[i].kor, stu[i].eng, stu[i].math, stu[i].average, stu[i].grade);     
    }
         

    //printf("학번 : %d\n", max.id);         // 최고 학점 학생의 학번 출력
	//printf("이름 : %s\n", max.name);       // 최고 학점 학생의 이름 출력
	//printf("학점 : %.1lf\n", max.grade);   // 최고 학점 학생의 학점 출력

	return 0;
}


int advanced_selection_sort(int* arr, int size)
{
        int i,j;
        int temp;
        int max;
        for (i = 0; i < size-1; i++) {
                max = i;
        for (j = i + 1; j < size; j++) {
                        if (arr[max] < arr[j]) {
                                max = j;
                        }
                }
                if (max != i){
                        temp = arr[i];
                        arr[i] = arr[max];
                        arr[max] = temp;
                }
        }

        return arr[0];
}

