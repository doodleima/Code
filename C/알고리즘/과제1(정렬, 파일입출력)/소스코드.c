// 과  제    1
// 과       목 : 알고리즘
// 담 당 교 수 : 정 일 용

// 학       과 : IT융합대학 컴퓨터공학과
// 학       번 : 20134888
// 학년 / 이름 : 2 / 임형열
// 제 출 일 자 : 2018.10.6.(토)

#define	_CRT_SECURE_NO_WARNINGS	// fopen() 사용

#include <stdio.h>
#include <string.h>

struct student {	// student 구조체 선언
	int OS, DC, CC;	// 각 과목의 성적 - 정수
	float Avg;	// 평균 - 실수
	char Name[20];	// 이름 저장할 배열
};

// 함수 및 (전역)변수
int grade_A, grade_B, grade_F = 0;	// AvgSort에 필요한 변수(분류한 값 저장)

void AvgSort(float Avg) {	// 평균값에 따라 인원 수 분류하는 AvgSort() 함수 선언 및 구현
	
	if (Avg == 40)	// 평균값 40일 경우
		grade_F++;
		
	else if (Avg == 80)	// 평균값 80일 경우
		grade_B++;
	
	else {
		switch ((int) (Avg / 10)) {	// 평균을 10으로 나눈 몫에 대하여 수행
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

		default:	// 그 외의 값(1~39)
			grade_F++;
			break;
		}
	}

}

void swapScore(int *a, int *b);	// swapScore - 매개변수 integer
void swapScore2(float *a, float *b);	// swapScore - 매개변수 float
void swapName(char *a, char *b);


int main() {	// main함수 구현

	FILE *os1, *os2;	// file 포인터 os1, os2 선언

	struct student Stu[7];	// student 구조체 형태 배열(array) 7개 생성

	int OS_sum = 0, DC_sum = 0, CC_sum = 0;
	float OS_avg, DC_avg, CC_avg, Total_avg = 0;
	// OS, DC, CC성적 합계의 평균, 총 합계의 평균

	int i, j; // 반복문 변수 i, j

	// if ((os1 = fopen("os1.txt", "r")) == NULL) {
	if ((os1 = fopen("C:\\Users\\Administrator\\Desktop\\os1.txt", "r")) == NULL) {	// os1.txt 열기(read)
		printf("파일을 열 수 없습니다!\n");
		return;	
	}	// 파일 없을시 메시지 출력 후 return

	fseek(os1, 14, SEEK_SET);	// 파일 포인터 이동, 시작점에서 14바이트 뒤까지 - 제일 윗부분 넘어감 : Name, OS, DC, CC 부분

	for (i = 0; i < 7; i++) {	
		fscanf(os1, "%s%d%d%d", &Stu[i].Name, &Stu[i].OS, &Stu[i].DC, &Stu[i].CC);	// 이름, OS, DC, CC 성적 입력받음
		Stu[i].Avg = (float)(Stu[i].OS + Stu[i].DC + Stu[i].CC) / 3;	// 각 학생의 평균값 산출하여 저장
	}
	// os1.txt에서 학생들의 이름과 성적을 입력받고 평균값 산출하여 각각의 배열에 저장

	// os1.txt에서 읽어들인 내용을 화면에 출력
	printf("1. os1.txt에서 읽어들인 내용입니다.\n");
	printf("\nNo\tName\tOS\tDC\tCC\n");
	for (i = 0; i < 7; i++)
		printf("%d\t%s\t%d\t%d\t%d\n", i+1, Stu[i].Name, Stu[i].OS, Stu[i].DC, Stu[i].CC);
	// os1.txt에서 읽어들인 내용 출력 끝

	// OS 성적 내림차순으로 정렬 후 이름 순서대로 정렬
	for (i = 0; i < 7; i++) {
		for (j = 6; j >= i; j--) {
			if (Stu[i].OS < Stu[j].OS) {	// OS성적 비교하여 뒤가 앞보다 크다면
				
				swapScore(&Stu[i].OS, &Stu[j].OS);
				swapScore(&Stu[i].DC, &Stu[j].DC);
				swapScore(&Stu[i].CC, &Stu[j].CC);
				swapScore2(&Stu[i].Avg, &Stu[j].Avg);

				swapName(Stu[i].Name, Stu[j].Name);	// 자리바꿈
			}
			else if (Stu[i].OS == Stu[j].OS) {	// OS성적이 같다면 - 이름 순서대로 정렬
				
				if (strcmp(Stu[i].Name, Stu[j].Name) > 0) {	// 문자열 비교하여 양수라면(i가 j보다 뒷 순서라면)

					swapScore(&Stu[i].OS, &Stu[j].OS);
					swapScore(&Stu[i].DC, &Stu[j].DC);
					swapScore(&Stu[i].CC, &Stu[j].CC);
					swapScore2(&Stu[i].Avg, &Stu[j].Avg);

					swapName(Stu[i].Name, Stu[j].Name);	// 자리바꿈
				}
			}
		}
	}	// 정렬 완료

	// 개인별 평균값과 과목별 합계 산출
	for (i = 0; i < 7; i++) {
		AvgSort(Stu[i].Avg);

		OS_sum += Stu[i].OS;
		DC_sum += Stu[i].DC;
		CC_sum += Stu[i].CC;
	}

	OS_avg = (float)(OS_sum / 7);	// OS 합계의 평균
	DC_avg = (float)(DC_sum / 7);	// DC 합계의 평균
	CC_avg = (float)(CC_sum / 7);	// CC 합계의 평균

	Total_avg = (OS_avg + DC_avg + CC_avg) / 3;	// 평균 합
	
	// os2 = fopen("os2.txt", "w+"); 
	os2 = fopen("C:\\Users\\Administrator\\Desktop\\os2.txt", "w+");	// os2.txt 열기(write+)

	// os2.txt에 쓰기
	fprintf(os2, "No\tName\tOS\tDC\tCC\tAVE\n");

	for (i = 0; i < 7; i++) {
		fprintf(os2, "%d\t%s\t%d\t%d\t%d\t%.0f\n", i+1, Stu[i].Name, Stu[i].OS, Stu[i].DC, Stu[i].CC, Stu[i].Avg);
	}

	fprintf(os2, "\n1-40 : %d\n", grade_F);
	fprintf(os2, "41-80 : %d\n", grade_B);
	fprintf(os2, "81-100 : %d\n", grade_A);

	fprintf(os2, "\nOS : %.0f\tDC : %.0f\tCC : %.0f\tTotal AVE : %.0f", OS_avg, DC_avg, CC_avg, Total_avg);	// 소수 첫째 자리에서 반올림(정수)

	// os2.txt에 저장한 내용을 화면에 출력
	printf("\n\n2. os2.txt에 저장할 내용을 출력합니다.\n");
	printf("\nNo\tName\tOS\tDC\tCC\tAVE\n");

	for (i = 0; i < 7; i++)
		printf("%d\t%s\t%d\t%d\t%d\t%.0f\n", i + 1, Stu[i].Name, Stu[i].OS, Stu[i].DC, Stu[i].CC, Stu[i].Avg);

	printf("\n1-40 : %d\n", grade_F);
	printf("41-80 : %d\n", grade_B);
	printf("81-100 : %d\n", grade_A);

	printf("\nOS : %.0f\tDC : %.0f\tCC : %.0f\tTotal AVE : %.0f\n", OS_avg, DC_avg, CC_avg, Total_avg);

	printf("\n출력한 내용이 os2.txt에 저장되었습니다.\n");
	// os2.txt에 복사한 내용 출력 끝

	fclose(os1);	// file 포인터 os1 닫음
	fclose(os2);	// file 포인터 os2 닫음

	// return;
}

// 함수 구현 : 교환
// 정수부 교환
void swapScore(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

// 실수부 교환
void swapScore2(float *a, float *b) {
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

// 이름 교환
void swapName(char *a, char *b) {
	char tmp[20];
	strcpy(tmp, a);
	strcpy(a, b);
	strcpy(b, tmp);
}