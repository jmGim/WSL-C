#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define LIST_MAX_COUNT 100000000	// 전체 리스트 크기
#define IS_PRINT_LIST_ALL 0		// 리스트 전체 출력 여부
#define ORDER_TYPE 1			// 0 : DESC, 1 : ASC

#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

// 리스트(배열)의 두 요소를 변환하는 함수
void Swap(int* _listNum, int _iLeft, int _iRight)
{
	if (_iLeft == _iRight)
		return;

	int tmp = _listNum[_iLeft];
	_listNum[_iLeft] = _listNum[_iRight];
	_listNum[_iRight] = tmp;
}
// 리스트(배열)를 출력하는 함수
void Print_List(int* _listNum)
{
#if IS_PRINT_LIST_ALL
	for (int i = 0; i < LIST_MAX_COUNT; i++)
		printf("%8d", _listNum[i]);
	printf("\n\n");
#else
	printf("%d ~ %d : ", MAX(0, LIST_MAX_COUNT - 10), LIST_MAX_COUNT - 1);
	for (int i = MAX(0, LIST_MAX_COUNT - 10); i < LIST_MAX_COUNT; i++)
		printf("%8d", _listNum[i]);
	printf("\n\n");
#endif
}

void quickSort(int* arr, int L, int R) {

	//피벗 인덱스 구하기
	int pivotIndex = (L + R) / 2;

	//피벗 값 구히가
	int pivot = arr[pivotIndex];

	//종료 조건 넣기
	if (L >= R) return;

	//움직일 두 커서 i, j, 추후 재귀호출 할 때 L, R값을 사용해야 하기 때문
	int i = L;
	int j = R;

	while (i <= j) {

		//i를 움직여 pivot 보다 큰 값을 왼쪽부터 찾기
		while (arr[i] < pivot) {
			i++;
		}

		//j를 움직여 pivot 보다 작은 값을 오른쪽부터 찾기
		while (arr[j] > pivot){
			j--;
		}

		//i가 j보다 크거나 같으면 while문 종료
		if (i <= j) {
			Swap(arr, i++, j--);
		}

	}
	if (L < j) quickSort(arr, L, j);
	if (i < R) quickSort(arr, i, R);
}

void Quick_Sort(int* _listNum, int _iLeft, int _iRight)
{
	// 리스트(배열)의 크기가 2개 미만이면 패스
	int iCnt = _iRight - _iLeft + 1;
	if (iCnt < 2) return;

	// 가장 왼쪽 요소를 피벗으로 사용
	// [3] [1] [4] [1] [5] [9] [2]
	// [P] [L] [ ] [ ] [ ] [ ] [R]
	int iPivot = _iLeft;
	int iL = _iLeft + 1;
	int iR = _iRight;

	// 피벗 기준 작은 값과 큰 값을 찾아 서로 변경
	// iR : 우측에서부터 변경할 값 검색 (오름차순 정렬 시 피벗보다 작은 값)
	// iL : 좌측에서부터 변경할 값 검색 (오름차순 정렬 시 피벗보다 큰 값)
	// 
	// 1 : [3] [1] [4] [1] [5] [9] [2]
	//     [P] [ ] [L] [ ] [ ] [ ] [R]
	// 2 : [3] [1] [2] [1] [5] [9] [4]
	//     [P] [ ] [L] [ ] [ ] [ ] [R]
	bool isSwap = false;
	while (iL < iR)
	{
#if ORDER_TYPE
		while (iL < iR && _listNum[iR] > _listNum[iPivot])// 왼쪽 인덱스 <  오른쪽 인덱스 // 오른쪽 값 >= 피벗의 값
#else
		while (iL < iR && _listNum[iR] < _listNum[iPivot])
#endif
			iR--;

#if ORDER_TYPE
		while (iL < iR && _listNum[iL] <= _listNum[iPivot])// 왼쪽 인덱스 <  오른쪽 인덱스 // 왼쪽 값 <= 피벗의 값
#else
		while (iL < iR && _listNum[iL] >= _listNum[iPivot])
#endif
			iL++;

		if (iL < iR)
			Swap(_listNum, iL, iR);
	}

	// iL 과 iR 이 만나면
	// 피벗 값을 그 경계로 옮겨 다음과 같은 형태로 변경
	// 전 : [피벗] [피벗보다 작은 그룹] [피벗보다 큰 그룹]
	// 후 : [피벗보다 작은 그룹] [피벗] [피벗보다 큰 그룹]
	//
	// 1 : [3] [1] [2] [1] [5] [9] [4]
	//     [P] [ ] [ ] [LR][ ] [ ] [ ]
	// 2 : [1] [1] [2] [3] [5] [9] [4]
	//     [P] [ ] [ ] [LR][ ] [ ] [R]
#if ORDER_TYPE
	if (_listNum[iPivot] > _listNum[iL])
#else
	if (_listNum[iPivot] < _listNum[iL])
#endif
	{
		Swap(_listNum, iPivot, iL);
		isSwap = true;
	}

	// [피벗보다 작은 그룹]과 [피벗보다 큰 그룹] 도 퀵 정렬
	if (iL > _iLeft)
		Quick_Sort(_listNum, _iLeft, iL - 1);
	if (iL < _iRight)
		Quick_Sort(_listNum, isSwap ? iL + 1 : iL, _iRight);
}

int cmpfunc(const void* a, const void* b);

int main()
{
#pragma region Init
	// 난수 초기화
	//srand((unsigned int)time(NULL));
	srand(0);

	// 리스트 생성
	int* listNum = NULL;
	listNum = calloc(LIST_MAX_COUNT, sizeof(int));
	if (NULL == listNum)
		return -1;

	clock_t start, end;
#pragma endregion

#pragma region Process Quick_Sort
	// 난수 채우기
	for (int i = 0; i < LIST_MAX_COUNT; i++)
		//listNum[i] = (rand() * rand()) % 999999 + 1;
		listNum[i] = (rand() << 15 | rand()) % (LIST_MAX_COUNT + 1);

	// 정렬 전 출력
	printf("정렬 전 데이터 :\n");
	Print_List(listNum);

	// 정렬
	start = clock();
	Quick_Sort(listNum, 0, LIST_MAX_COUNT - 1);
	end = clock();

	// 정렬 후 출력
	printf("Quick_Sort 정렬 후 데이터 :\n");
	Print_List(listNum);

	printf("수행 시간 : %.3lfs\n", (double)(end - start) / CLOCKS_PER_SEC);
#pragma endregion

#pragma region Process qsort
	srand(0);

	// 난수 채우기
	for (int i = 0; i < LIST_MAX_COUNT; i++)
		//listNum[i] = (rand() * rand()) % 999999 + 1;
		listNum[i] = (rand() << 15 | rand()) % (LIST_MAX_COUNT + 1);

	// 정렬 전 출력
	/*printf("정렬 전 데이터 :\n");
	Print_List(listNum);*/
	printf("\n");

	// 정렬
	start = clock();
	qsort(listNum, LIST_MAX_COUNT, sizeof(int), cmpfunc);
	end = clock();

	// 정렬 후 출력
	printf("qsort 정렬 후 데이터 :\n");
	Print_List(listNum);

	printf("수행 시간 : %.3lfs\n", (double)(end - start) / CLOCKS_PER_SEC);
#pragma endregion

#pragma region Process Quick_Sort2
	srand(0);

	// 난수 채우기
	for (int i = 0; i < LIST_MAX_COUNT; i++)
		//listNum[i] = (rand() * rand()) % 999999 + 1;
		listNum[i] = (rand() << 15 | rand()) % (LIST_MAX_COUNT + 1);

	// 정렬 전 출력
	/*printf("정렬 전 데이터 :\n");
	Print_List(listNum);*/
	printf("\n");

	// 정렬
	start = clock();
	quickSort(listNum, 0, LIST_MAX_COUNT - 1);
	end = clock();

	// 정렬 후 출력
	printf("Quick_Sort2 정렬 후 데이터 : \n");
	Print_List(listNum);

	printf("수행 시간 : %.3lfs\n", (double)(end - start) / CLOCKS_PER_SEC);
#pragma endregion


#pragma region Release
	if (NULL != listNum) // => list = NULL 로 실수했을 때 오류발생 안함, 반대로 써서 오류 유도 후 찾기 편하게 하기
	{
		free(listNum);
		listNum = NULL;//free를 하면 NULL로 비워주는게 국룰
	}
#pragma endregion
}

int cmpfunc(const void* a, const void* b)
{
#if ORDER_TYPE
	return (*(int*)a - *(int*)b);
#else
	return (*(int*)b - *(int*)a);
#endif
}
