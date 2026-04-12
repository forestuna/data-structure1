#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define_CRT_SECURE_NO_WARNINGS

// 학생 정보를 담을 구조체 정의
typedef struct {
    char name[20];
    int id;
    int score;
} Student;

int main() {
    int N;
    int sum = 0;
    char namePool[100][20]; // 파일에서 읽어온 이름들을 저장할 배열 (최대 100개)
    int nameCount = 0;

    // 난수 생성을 위한 시드 설정
    srand(time(NULL));

    // 1. 파일에서 이름 리스트 읽기
    FILE *file = fopen("name_list.txt", "r");
    if (file == NULL) {
        printf("오류: name_list.txt 파일을 찾을 수 없습니다.\n");
        return 1;
    }

    // 파일 끝까지 이름을 읽어 namePool에 저장
    while (nameCount < 100 && fscanf(file, "%s", namePool[nameCount]) != EOF) {
        nameCount++;
    }
    fclose(file);

    if (nameCount == 0) {
        printf("오류: 파일에 이름 데이터가 없습니다.\n");
        return 1;
    }

    printf("학생 수 N을 입력하세요: ");
    scanf("%d", &N);

    // 2. 구조체 배열 동적 할당 (malloc 사용)
    Student *students = (Student *)malloc(sizeof(Student) * N);
    if (students == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // 3. 데이터 입력 및 무작위 생성
    for (int i = 0; i < N; i++) {
        // 이름 리스트에서 무작위로 선택하여 복사
        int randomIdx = rand() % nameCount;
        strcpy(students[i].name, namePool[randomIdx]);
       
        // 학번은 1부터 순차 부여
        students[i].id = i + 1;
       
        // 성적은 1 ~ 100 사이 무작위 정수
        students[i].score = (rand() % 100) + 1;

        // 평균 계산을 위한 합계 누적
        sum += students[i].score;
    }

    // 초기값 설정 (인덱스 연산자 활용)
    int maxIdx = 0;
    int minIdx = 0;

    // 4. 최고/최저 점수 학생 탐색
    for (int i = 1; i < N; i++) {
        if (students[i].score > students[maxIdx].score) {
            maxIdx = i;
        }
        if (students[i].score < students[minIdx].score) {
            minIdx = i;
        }
    }

    // 5. 결과 출력
    printf("\n--- 전체 학생 성적 리스트 ---\n");
    for (int i = 0; i < N; i++) {
        printf("[%d] 이름: %s | 학번: %d | 성적: %d\n",
                i, students[i].name, students[i].id, students[i].score);
    }

    printf("\n--- 분석 결과 ---\n");
    printf("최고점 학생: %s (학번: %d, 성적: %d)\n",
            students[maxIdx].name, students[maxIdx].id, students[maxIdx].score);
    printf("최저점 학생: %s (학번: %d, 성적: %d)\n",
            students[minIdx].name, students[minIdx].id, students[minIdx].score);
    printf("평균 점수: %.2f\n", (float)sum / N);

    // 6. 메모리 해제
    free(students);

    return 0;
}
