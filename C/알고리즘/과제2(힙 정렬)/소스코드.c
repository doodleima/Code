// 과  제    2
// 과       목 : 알고리즘
// 담 당 교 수 : 정 일 용

// 학       과 : IT융합대학 컴퓨터공학과
// 학       번 : 20134888
// 학년 / 이름 : 2 / 임형열
// 제 출 일 자 : 2018.11.4.(일)

#define	_CRT_SECURE_NO_WARNINGS	// fopen() 사용

#include <stdio.h>
#include <string.h>

void heapify(int *array, int size, int middle);
void heapSort(int *array, int size);
void buildHeap(int *array, int size);

void swap(int *array, int a, int b) {	// 자리교체
	int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

int main() {

	FILE *os1, *os2;	// file 포인터 os1, os2 선언

	int Array[15];	// 크기 15인 정수형 배열 Array 선언(index = 0 ~ 14)

	int i;
	int length = sizeof(Array) / sizeof(int);	// Array 배열의 크기를 나타내는 정수 length = 15


	// if ((os1 = fopen("os1.txt", "r")) == NULL) {
	if ((os1 = fopen("C:\\Users\\Administrator\\Desktop\\os1.txt", "r")) == NULL) {	// os1.txt 열기(read)
		printf("파일을 열 수 없습니다!\n");
		return;
	}	// 파일 없을시 메시지 출력 후 return

	for (i = 0; i < length; i++) {	// 15번 반복(0 ~ 14)
		fscanf(os1, "%d", &Array[i]);
	}

	// os1.txt에서 읽어들인 내용을 화면에 출력
	printf("1. os1.txt에서 읽어들인 내용입니다.\n");
	for (i = 0; i < length; i++) {	// 15번 반복(0 ~ 14)
		printf("%d ", Array[i]);
	}
	printf("\n\n");

	buildHeap(Array, length);	// 배열을 힙 구조로 만듦

	// os2 = fopen("os2.txt", "w+") {
	os2 = fopen("C:\\Users\\Administrator\\Desktop\\os2.txt", "w+");	// os2.txt 열기(write+)	

	// 읽어들인 내용을 힙 구조로 만들어서 os2.txt에 저장
	fprintf(os2, "1.힙 구조 생성 : 3의 배수는 다른 수보다 작은 수로 취급함.\n");
	printf("2. 읽어들인 내용을 힙으로 만듭니다.\n");
	for (i = 0; i < length; i++) {	// 15번 반복(0 ~ 14)
		fprintf(os2, "%d ", Array[i]);	// os2에 쓰고
		printf("%d ", Array[i]);	// 출력
	}
	fprintf(os2, "\n\n");
	printf("\n\n");


	heapSort(Array, length);	// 힙 정렬 실행

	// 힙을 정렬하여 os2.txt에 저장
	fprintf(os2, "2. 힙 정렬 결과.\n");
	printf("3. 힙을 정렬한 결과입니다.\n");
	for (i = 0; i < length; i++) {	// 15번 반복(0 ~ 14)
		fprintf(os2, "%d ", Array[i]);	// os2에 쓰고
		printf("%d ", Array[i]);	// 출력
	}
	fprintf(os2, "\n");
	printf("\n");

	fclose(os1);	// 파일 포인터 닫기
	fclose(os2);	// 파일 포인터 닫기
}

void buildHeap(int *array, int size) {
	int middle = (size / 2) - 1;

	for (int i = middle; i >= 0; i--) {
		heapify(array, size, i);
	}
}

void heapSort(int *array, int size) {
	for (int i = size - 1; i > 0; i--) {
		swap(array, 0, i);
		heapify(array, i, 0);
	}
}

void heapify(int *array, int size, int a) {
	int Parent = a;
	int Left = a * 2 + 1;
	int Right = a * 2 + 2;

	if (Left < size) {
		if (array[Left] % 3 == 0 && array[Parent] % 3 == 0) {	// 부모와 왼쪽 자식 모두 3의 배수일 경우
			Parent = (array[Left] > array[Parent]) ? Left : Parent;	// 크기 비교 후 더 큰 쪽을 부모로
		}

		else if (array[Left] % 3 != 0 && array[Parent] % 3 == 0)	// 부모만 3의 배수일 경우
			Parent = Left;	//	왼쪽 자식이 더 큰 값
	
		else if (array[Left] % 3 == 0 && array[Parent] % 3 != 0)	// 왼쪽 자식만 3의 배수일 경우
			Parent = Parent;	// 부모가 더 큰 값
		
		else {	// 둘 다 3의 배수가 아닐 경우
			if (array[Parent] < array[Left]) {	
				Parent = Left;
			}
		}
	}

	if (Right < size) {
		if (array[Right] % 3 == 0 && array[Parent] % 3 == 0) {	// 부모와 오른쪽 자식 모두 3의 배수일 경우
			Parent = (array[Right] > array[Parent]) ? Right : Parent;	// 크기 비교 후 더 큰 쪽을 부모로
		}

		else if (array[Right] % 3 != 0 && array[Parent] % 3 == 0)	// 부모만 3의 배수일 경우
			Parent = Right;

		else if (array[Right] % 3 == 0 && array[Parent] % 3 != 0)	// 오른쪽 자식만 3의 배수일 경우
			Parent = Parent;	// 부모가 더 큰 값;

		else {	// 둘 다 3의 배수가 아닐 경우
			if (array[Parent] < array[Right]) {
				Parent = Right;
			}
		}
	}

	if (a != Parent) {	// 부모와 자식이 교체되었을 경우
		swap(array, Parent, a);
		heapify(array, size, Parent);	// heapify()호출 - 재귀
	}
}