// ��  ��    2
// ��       �� : �˰���
// �� �� �� �� : �� �� ��

// ��       �� : IT���մ��� ��ǻ�Ͱ��а�
// ��       �� : 20134888
// �г� / �̸� : 2 / ������
// �� �� �� �� : 2018.11.4.(��)

#define	_CRT_SECURE_NO_WARNINGS	// fopen() ���

#include <stdio.h>
#include <string.h>

void heapify(int *array, int size, int middle);
void heapSort(int *array, int size);
void buildHeap(int *array, int size);

void swap(int *array, int a, int b) {	// �ڸ���ü
	int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

int main() {

	FILE *os1, *os2;	// file ������ os1, os2 ����

	int Array[15];	// ũ�� 15�� ������ �迭 Array ����(index = 0 ~ 14)

	int i;
	int length = sizeof(Array) / sizeof(int);	// Array �迭�� ũ�⸦ ��Ÿ���� ���� length = 15


	// if ((os1 = fopen("os1.txt", "r")) == NULL) {
	if ((os1 = fopen("C:\\Users\\Administrator\\Desktop\\os1.txt", "r")) == NULL) {	// os1.txt ����(read)
		printf("������ �� �� �����ϴ�!\n");
		return;
	}	// ���� ������ �޽��� ��� �� return

	for (i = 0; i < length; i++) {	// 15�� �ݺ�(0 ~ 14)
		fscanf(os1, "%d", &Array[i]);
	}

	// os1.txt���� �о���� ������ ȭ�鿡 ���
	printf("1. os1.txt���� �о���� �����Դϴ�.\n");
	for (i = 0; i < length; i++) {	// 15�� �ݺ�(0 ~ 14)
		printf("%d ", Array[i]);
	}
	printf("\n\n");

	buildHeap(Array, length);	// �迭�� �� ������ ����

	// os2 = fopen("os2.txt", "w+") {
	os2 = fopen("C:\\Users\\Administrator\\Desktop\\os2.txt", "w+");	// os2.txt ����(write+)	

	// �о���� ������ �� ������ ���� os2.txt�� ����
	fprintf(os2, "1.�� ���� ���� : 3�� ����� �ٸ� ������ ���� ���� �����.\n");
	printf("2. �о���� ������ ������ ����ϴ�.\n");
	for (i = 0; i < length; i++) {	// 15�� �ݺ�(0 ~ 14)
		fprintf(os2, "%d ", Array[i]);	// os2�� ����
		printf("%d ", Array[i]);	// ���
	}
	fprintf(os2, "\n\n");
	printf("\n\n");


	heapSort(Array, length);	// �� ���� ����

	// ���� �����Ͽ� os2.txt�� ����
	fprintf(os2, "2. �� ���� ���.\n");
	printf("3. ���� ������ ����Դϴ�.\n");
	for (i = 0; i < length; i++) {	// 15�� �ݺ�(0 ~ 14)
		fprintf(os2, "%d ", Array[i]);	// os2�� ����
		printf("%d ", Array[i]);	// ���
	}
	fprintf(os2, "\n");
	printf("\n");

	fclose(os1);	// ���� ������ �ݱ�
	fclose(os2);	// ���� ������ �ݱ�
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
		if (array[Left] % 3 == 0 && array[Parent] % 3 == 0) {	// �θ�� ���� �ڽ� ��� 3�� ����� ���
			Parent = (array[Left] > array[Parent]) ? Left : Parent;	// ũ�� �� �� �� ū ���� �θ��
		}

		else if (array[Left] % 3 != 0 && array[Parent] % 3 == 0)	// �θ� 3�� ����� ���
			Parent = Left;	//	���� �ڽ��� �� ū ��
	
		else if (array[Left] % 3 == 0 && array[Parent] % 3 != 0)	// ���� �ڽĸ� 3�� ����� ���
			Parent = Parent;	// �θ� �� ū ��
		
		else {	// �� �� 3�� ����� �ƴ� ���
			if (array[Parent] < array[Left]) {	
				Parent = Left;
			}
		}
	}

	if (Right < size) {
		if (array[Right] % 3 == 0 && array[Parent] % 3 == 0) {	// �θ�� ������ �ڽ� ��� 3�� ����� ���
			Parent = (array[Right] > array[Parent]) ? Right : Parent;	// ũ�� �� �� �� ū ���� �θ��
		}

		else if (array[Right] % 3 != 0 && array[Parent] % 3 == 0)	// �θ� 3�� ����� ���
			Parent = Right;

		else if (array[Right] % 3 == 0 && array[Parent] % 3 != 0)	// ������ �ڽĸ� 3�� ����� ���
			Parent = Parent;	// �θ� �� ū ��;

		else {	// �� �� 3�� ����� �ƴ� ���
			if (array[Parent] < array[Right]) {
				Parent = Right;
			}
		}
	}

	if (a != Parent) {	// �θ�� �ڽ��� ��ü�Ǿ��� ���
		swap(array, Parent, a);
		heapify(array, size, Parent);	// heapify()ȣ�� - ���
	}
}