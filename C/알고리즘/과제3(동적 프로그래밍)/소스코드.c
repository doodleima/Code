// ��  ��    3
// ��       �� : �˰���
// �� �� �� �� : �� �� ��

// ��       �� : IT���մ��� ��ǻ�Ͱ��а�
// ��       �� : 20134888
// �г� / �̸� : 2 / ������
// �� �� �� �� : 2018.12.7.(��)

#define _CRT_SECURE_NO_WARNINGS	// scanf() ���

#include <stdio.h>
#include <malloc.h>	// malloc() ���

// �Լ� ����
int **makeArray(int n) {
	int **m = (int **)malloc(0);	// ���� �޸� �Ҵ� �� �ʱ�ȭ

	for (int i = 0; i < n; i ++) {
		m[i] = (int*)malloc(sizeof(int) * n);	// �Է¹��� ����(n)��ŭ ���� �޸� �Ҵ�
	}
	return m;
}

int *makeColRow(int n);	// �Է¹��� ����(n)��ŭ ��� ������ �����ϱ� ���� ��/�� �Է�
int minResult(int n, int a[], int *m[]);	// �ּڰ��� ���� ����� ���� ��� ��
void minSequence(int n, int k, int *m[]);	// �ּڰ��� ���� ����� ���� ����


// main �Լ�
int main() {	
	int *a, **b;
	int number, result = 0;

	printf("������ ������ ����� ������ �Է��ϼ��� : ");
	scanf("%d", &number);

	printf("\n");

	a = makeColRow(number);
	b = makeArray(number);

	result = minResult(number, a, b);


	printf("\n1. ��� ������ �ּڰ��� %d �Դϴ�.\n", result);
	printf("2. �ּڰ��� ���� ��� ���� ���� : ");
	minSequence(1, number, b);
	printf("\n");

	return;
}


// �Լ� ����
int *makeColRow(int n) {	// �Է¹��� ����(n)��ŭ ��� ������ �����ϱ� ���� ��/�� �Է�
	int *m;
	
	printf("%d�� ����� ��(+������ ���� ��) �Է� \n", n);

	m = (int*)malloc(sizeof(int) * n);	// �Է¹��� ����(n)��ŭ ���� �޸� �Ҵ�

	for (int i = 0; i < n + 1; i++) {

		if (i != n) {
			if (i+1 != n) {
				printf("%d��° ����� ��(%d��° ���� ��) �Է� : ", i + 1, i + 2);	// �Է¹��� ����+1 ��ŭ ���� �Է¹���
				scanf("%d", &m[i]);
			}

			else {
				printf("%d��° ����� �� �Է� : ", i + 1);	// �Է¹��� ����+1 ��ŭ ���� �Է¹���
				scanf("%d", &m[i]);
			}
		}

		else {
			printf("%d��° ����� �� �Է� : ", i);	// �Է¹��� ����+1 ��ŭ ���� �Է¹���
			scanf("%d", &m[i]);
		}
	}
	return m;
}

int minResult(int n, int a[], int *m[]) {	// �ּڰ��� ���� ����� ���� ��� ��
	int i, j, k;
	int check;
	int min = 0, temp = 0;
	int **b;

	b = makeArray(n + 1);	// makeArray() ȣ��

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

void minSequence(int n, int k, int *m[]) {	// �ּڰ��� ���� ����� ���� ����
	int a;

	if (n == k) {	// ��� ���, ����� AX(X = number) ���·� ���
		printf("A%d", n);
	}

	else {	// [] ���
		a = m[n][k];

		printf("[");

		// ����� ȣ��
		minSequence(n, a, m);
		minSequence(a + 1, k, m);

		printf("]");
	}
}