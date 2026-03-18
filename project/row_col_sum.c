/* #include <stdio.h>

#define ROW_SIZE 5
#define COL_SIZE 6
int main(void)
{
  int num_arr[ROW_SIZE][COL_SIZE] = { {1,2,3,4,5,0},
	  {6,7,8,9,10,0},
	  {11,12,13,14,15,0},
 	  {16,17,18,19,20,0},
	  {0,0,0,0,0,0}	  
  };

  int *p_row_sum[ROW_SIZE-1] = {num_arr[0], num_arr[1], num_arr[2], num_arr[3]};
  int *p_col_sum = num_arr[4];

  int i, j;

   

  for (i = 0; i < ROW_SIZE-1; i++)  
  {
	for (j = 0; j < COL_SIZE-1; j++)
	{
		num_arr[i][COL_SIZE-1] += num_arr[i][j];

	}
	printf("\n");       // 한 행(부분배열)을 출력한 후에 줄 바꿈
  }


  for (j = 0; j < COL_SIZE-1; j++){
	for (i = 0; i < ROW_SIZE-1; i++) {
		num_arr[ROW_SIZE-1][j] += num_arr[i][j];
	}
	num_arr[ROW_SIZE-1][COL_SIZE-1] += num_arr[ROW_SIZE-1][j];  
	  
  }

  for (i = 0; i < ROW_SIZE; i++ ) {
	for (j = 0; j < COL_SIZE; j++){
		printf("%5d", num_arr[i][j]);
	}
	printf("\n");
  }

  return 0;
} */



#include <stdio.h>

#define ROW_SIZE 5
#define COL_SIZE 6

int main(void)
{
	int num_arr[ROW_SIZE][COL_SIZE] = { {1,2,3,4,5,0},
			{6,7,8,9,10,0},
			{11,12,13,14,15,0},
			{16,17,18,19,20,0},
			{0,0,0,0,0,0}
	};

	int* p_row_sum[ROW_SIZE] = { num_arr[0], num_arr[1], num_arr[2], num_arr[3], num_arr[4]};
	//int* p_col_sum[6] = { num_arr[4] };

	int i, j;



	for (i = 0; i < ROW_SIZE - 1; i++)
	{
		for (j = 0; j < COL_SIZE - 1; j++)
		{
			p_row_sum[i][COL_SIZE - 1] += p_row_sum[i][j];

		}
		printf("\n");       // 한 행(부분배열)을 출력한 후에 줄 바꿈
	}


	for (j = 0; j < COL_SIZE - 1; j++) {
		for (i = 0; i < ROW_SIZE - 1; i++) {
			p_row_sum[ROW_SIZE - 1][j] += p_row_sum[i][j];
		}
		p_row_sum[ROW_SIZE - 1][COL_SIZE - 1] += p_row_sum[ROW_SIZE-1][j];

	}

	for (i = 0; i < ROW_SIZE; i++) {
		for (j = 0; j < COL_SIZE; j++) {
			printf("%5d", p_row_sum[i][j]);
		}
		printf("\n");
	}

	return 0;
}
