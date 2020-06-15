// ��  ��    1
// ��       �� : �˰���
// �� �� �� �� : �� �� ��

// ��       �� : IT���մ��� ��ǻ�Ͱ��а�
// ��       �� : 20134888
// �г� / �̸� : 2 / ������
// �� �� �� �� : 2018.10.6.(��)

#define	_CRT_SECURE_NO_WARNINGS	// fopen() ���

#include <stdio.h>
#include <string.h>

struct student {	// student ����ü ����
	int OS, DC, CC;	// �� ������ ���� - ����
	float Avg;	// ��� - �Ǽ�
	char Name[20];	// �̸� ������ �迭
};

// �Լ� �� (����)����
int grade_A, grade_B, grade_F = 0;	// AvgSort�� �ʿ��� ����(�з��� �� ����)

void AvgSort(float Avg) {	// ��հ��� ���� �ο� �� �з��ϴ� AvgSort() �Լ� ���� �� ����
	
	if (Avg == 40)	// ��հ� 40�� ���
		grade_F++;
		
	else if (Avg == 80)	// ��հ� 80�� ���
		grade_B++;
	
	else {
		switch ((int) (Avg / 10)) {	// ����� 10���� ���� �� ���Ͽ� ����
		case 10:
		case 9:
		case 8:	// 81 ~ 100
			grade_A++;
			break;

		case 7:
		case 6:
		case 5:
		case 4:	// 41 ~ 79
			grade_B++;
			break;

		default:	// �� ���� ��(1~39)
			grade_F++;
			break;
		}
	}

}

void swapScore(int *a, int *b);	// swapScore - �Ű����� integer
void swapScore2(float *a, float *b);	// swapScore - �Ű����� float
void swapName(char *a, char *b);


int main() {	// main�Լ� ����

	FILE *os1, *os2;	// file ������ os1, os2 ����

	struct student Stu[7];	// student ����ü ���� �迭(array) 7�� ����

	int OS_sum = 0, DC_sum = 0, CC_sum = 0;
	float OS_avg, DC_avg, CC_avg, Total_avg = 0;
	// OS, DC, CC���� �հ��� ���, �� �հ��� ���

	int i, j; // �ݺ��� ���� i, j

	// if ((os1 = fopen("os1.txt", "r")) == NULL) {
	if ((os1 = fopen("C:\\Users\\Administrator\\Desktop\\os1.txt", "r")) == NULL) {	// os1.txt ����(read)
		printf("������ �� �� �����ϴ�!\n");
		return;	
	}	// ���� ������ �޽��� ��� �� return

	fseek(os1, 14, SEEK_SET);	// ���� ������ �̵�, ���������� 14����Ʈ �ڱ��� - ���� ���κ� �Ѿ : Name, OS, DC, CC �κ�

	for (i = 0; i < 7; i++) {	
		fscanf(os1, "%s%d%d%d", &Stu[i].Name, &Stu[i].OS, &Stu[i].DC, &Stu[i].CC);	// �̸�, OS, DC, CC ���� �Է¹���
		Stu[i].Avg = (float)(Stu[i].OS + Stu[i].DC + Stu[i].CC) / 3;	// �� �л��� ��հ� �����Ͽ� ����
	}
	// os1.txt���� �л����� �̸��� ������ �Է¹ް� ��հ� �����Ͽ� ������ �迭�� ����

	// os1.txt���� �о���� ������ ȭ�鿡 ���
	printf("1. os1.txt���� �о���� �����Դϴ�.\n");
	printf("\nNo\tName\tOS\tDC\tCC\n");
	for (i = 0; i < 7; i++)
		printf("%d\t%s\t%d\t%d\t%d\n", i+1, Stu[i].Name, Stu[i].OS, Stu[i].DC, Stu[i].CC);
	// os1.txt���� �о���� ���� ��� ��

	// OS ���� ������������ ���� �� �̸� ������� ����
	for (i = 0; i < 7; i++) {
		for (j = 6; j >= i; j--) {
			if (Stu[i].OS < Stu[j].OS) {	// OS���� ���Ͽ� �ڰ� �պ��� ũ�ٸ�
				
				swapScore(&Stu[i].OS, &Stu[j].OS);
				swapScore(&Stu[i].DC, &Stu[j].DC);
				swapScore(&Stu[i].CC, &Stu[j].CC);
				swapScore2(&Stu[i].Avg, &Stu[j].Avg);

				swapName(Stu[i].Name, Stu[j].Name);	// �ڸ��ٲ�
			}
			else if (Stu[i].OS == Stu[j].OS) {	// OS������ ���ٸ� - �̸� ������� ����
				
				if (strcmp(Stu[i].Name, Stu[j].Name) > 0) {	// ���ڿ� ���Ͽ� ������(i�� j���� �� �������)

					swapScore(&Stu[i].OS, &Stu[j].OS);
					swapScore(&Stu[i].DC, &Stu[j].DC);
					swapScore(&Stu[i].CC, &Stu[j].CC);
					swapScore2(&Stu[i].Avg, &Stu[j].Avg);

					swapName(Stu[i].Name, Stu[j].Name);	// �ڸ��ٲ�
				}
			}
		}
	}	// ���� �Ϸ�

	// ���κ� ��հ��� ���� �հ� ����
	for (i = 0; i < 7; i++) {
		AvgSort(Stu[i].Avg);

		OS_sum += Stu[i].OS;
		DC_sum += Stu[i].DC;
		CC_sum += Stu[i].CC;
	}

	OS_avg = (float)(OS_sum / 7);	// OS �հ��� ���
	DC_avg = (float)(DC_sum / 7);	// DC �հ��� ���
	CC_avg = (float)(CC_sum / 7);	// CC �հ��� ���

	Total_avg = (OS_avg + DC_avg + CC_avg) / 3;	// ��� ��
	
	// os2 = fopen("os2.txt", "w+"); 
	os2 = fopen("C:\\Users\\Administrator\\Desktop\\os2.txt", "w+");	// os2.txt ����(write+)

	// os2.txt�� ����
	fprintf(os2, "No\tName\tOS\tDC\tCC\tAVE\n");

	for (i = 0; i < 7; i++) {
		fprintf(os2, "%d\t%s\t%d\t%d\t%d\t%.0f\n", i+1, Stu[i].Name, Stu[i].OS, Stu[i].DC, Stu[i].CC, Stu[i].Avg);
	}

	fprintf(os2, "\n1-40 : %d\n", grade_F);
	fprintf(os2, "41-80 : %d\n", grade_B);
	fprintf(os2, "81-100 : %d\n", grade_A);

	fprintf(os2, "\nOS : %.0f\tDC : %.0f\tCC : %.0f\tTotal AVE : %.0f", OS_avg, DC_avg, CC_avg, Total_avg);	// �Ҽ� ù° �ڸ����� �ݿø�(����)

	// os2.txt�� ������ ������ ȭ�鿡 ���
	printf("\n\n2. os2.txt�� ������ ������ ����մϴ�.\n");
	printf("\nNo\tName\tOS\tDC\tCC\tAVE\n");

	for (i = 0; i < 7; i++)
		printf("%d\t%s\t%d\t%d\t%d\t%.0f\n", i + 1, Stu[i].Name, Stu[i].OS, Stu[i].DC, Stu[i].CC, Stu[i].Avg);

	printf("\n1-40 : %d\n", grade_F);
	printf("41-80 : %d\n", grade_B);
	printf("81-100 : %d\n", grade_A);

	printf("\nOS : %.0f\tDC : %.0f\tCC : %.0f\tTotal AVE : %.0f\n", OS_avg, DC_avg, CC_avg, Total_avg);

	printf("\n����� ������ os2.txt�� ����Ǿ����ϴ�.\n");
	// os2.txt�� ������ ���� ��� ��

	fclose(os1);	// file ������ os1 ����
	fclose(os2);	// file ������ os2 ����

	// return;
}

// �Լ� ���� : ��ȯ
// ������ ��ȯ
void swapScore(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

// �Ǽ��� ��ȯ
void swapScore2(float *a, float *b) {
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

// �̸� ��ȯ
void swapName(char *a, char *b) {
	char tmp[20];
	strcpy(tmp, a);
	strcpy(a, b);
	strcpy(b, tmp);
}