// 과  제    3
// 과       목 : 알고리즘
// 담 당 교 수 : 정 일 용

// 학       과 : IT융합대학 컴퓨터공학과
// 학       번 : 20134888
// 학년 / 이름 : 2 / 임형열
// 제 출 일 자 : 2018.12.7.(금)

#define _CRT_SECURE_NO_WARNINGS	// scanf() 사용

#include <stdio.h>
#include <malloc.h>	// malloc() 사용

// 함수 선언
int **makeArray(int n) {
	int **m = (int **)malloc(0);	// 동적 메모리 할당 및 초기화

	for (int i = 0; i < n; i ++) {
		m[i] = (int*)malloc(sizeof(int) * n);	// 입력받은 갯수(n)만큼 동적 메모리 할당
	}
	return m;
}

int *makeColRow(int n);	// 입력받은 갯수(n)만큼 행렬 곱셈을 수행하기 위해 행/열 입력
int minResult(int n, int a[], int *m[]);	// 최솟값을 갖는 행렬의 곱셈 결과 값
void minSequence(int n, int k, int *m[]);	// 최솟값을 갖는 행렬의 곱셈 순서


// main 함수
int main() {	
	int *a, **b;
	int number, result = 0;

	printf("곱셈을 실행할 행렬의 갯수를 입력하세요 : ");
	scanf("%d", &number);

	printf("\n");

	a = makeColRow(number);
	b = makeArray(number);

	result = minResult(number, a, b);


	printf("\n1. 행렬 곱셈의 최솟값은 %d 입니다.\n", result);
	printf("2. 최솟값을 갖는 행렬 곱셈 순서 : ");
	minSequence(1, number, b);
	printf("\n");

	return;
}


// 함수 구현
int *makeColRow(int n) {	// 입력받은 갯수(n)만큼 행렬 곱셈을 수행하기 위해 행/열 입력
	int *m;
	
	printf("%d개 행렬의 행(+마지막 행의 열) 입력 \n", n);

	m = (int*)malloc(sizeof(int) * n);	// 입력받은 갯수(n)만큼 동적 메모리 할당

	for (int i = 0; i < n + 1; i++) {

		if (i != n) {
			if (i+1 != n) {
				printf("%d번째 행렬의 행(%d번째 행의 열) 입력 : ", i + 1, i + 2);	// 입력받은 갯수+1 만큼 값을 입력받음
				scanf("%d", &m[i]);
			}

			else {
				printf("%d번째 행렬의 행 입력 : ", i + 1);	// 입력받은 갯수+1 만큼 값을 입력받음
				scanf("%d", &m[i]);
			}
		}

		else {
			printf("%d번째 행렬의 열 입력 : ", i);	// 입력받은 갯수+1 만큼 값을 입력받음
			scanf("%d", &m[i]);
		}
	}
	return m;
}

int minResult(int n, int a[], int *m[]) {	// 최솟값을 갖는 행렬의 곱셈 결과 값
	int i, j, k;
	int check;
	int min = 0, temp = 0;
	int **b;

	b = makeArray(n + 1);	// makeArray() 호출

	for (i = 1; i < n+1; i ++) {
		b[i][i] = 0;
	}

	for (check = 1; check < n; check ++) {
		for (i = 1; i <= n - check; i ++) {
			j = check + i;

			for (k = i; k < j; k ++) {
				b[i][j] = b[i][k] + b[k + 1][j] + a[i - 1] * a[k] * a[j];

				if (i == k) {
					temp = b[i][j];
					min = k;
				}

				else if (b[i][j] > temp) {
					b[i][j] = temp;
				}

				else {
					min = k;
				}
			}
			m[i][j] = min;
		}
	}
	return b[1][n];
}

void minSequence(int n, int k, int *m[]) {	// 최솟값을 갖는 행렬의 곱셈 순서
	int a;

	if (n == k) {	// 행렬 출력, 행렬은 AX(X = number) 형태로 출력
		printf("A%d", n);
	}

	else {	// [] 출력
		a = m[n][k];

		printf("[");

		// 재귀적 호출
		minSequence(n, a, m);
		minSequence(a + 1, k, m);

		printf("]");
	}
}