#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char name[20];
    int id;
    int score;
} Student;

int main() {
    int N;
    int sum = 0;
    char namePool[100][20];
    int nameCount = 0;

    srand(time(NULL));

    // 1. 파일에서 이름 리스트 읽기
    FILE *file = fopen("name_list.txt", "r");
    if (file == NULL) {
        printf("오류: name_list.txt 파일을 찾을 수 없습니다.\n");
        return 1;
    }

    // namePool[nameCount] 대신 *(namePool + nameCount) 사용
    while (nameCount < 100 && fscanf(file, "%s", *(namePool + nameCount)) != EOF) {
        nameCount++;
    }
    fclose(file);

    if (nameCount == 0) {
        printf("오류: 파일에 이름 데이터가 없습니다.\n");
        return 1;
    }

    printf("학생 수 N을 입력하세요: ");
    scanf("%d", &N);

    // 2. 구조체 배열 동적 할당
    Student *students = (Student *)malloc(sizeof(Student) * N);
    if (students == NULL) return 1;

    // 3. 데이터 입력 및 무작위 생성 (포인터 연산 적용)
    for (int i = 0; i < N; i++) {
        int randomIdx = rand() % nameCount;
       
        // students[i].name 대신 (students + i)->name 또는 (*(students + i)).name
        strcpy((*(students + i)).name, *(namePool + randomIdx));
       
        (*(students + i)).id = i + 1;
        (*(students + i)).score = (rand() % 100) + 1;

        sum += (*(students + i)).score;
    }

    int maxIdx = 0;
    int minIdx = 0;

    // 4. 최고/최저 점수 탐색 (포인터 연산 적용)
    for (int i = 1; i < N; i++) {
        if ((*(students + i)).score > (*(students + maxIdx)).score) {
            maxIdx = i;
        }
        if ((*(students + i)).score < (*(students + minIdx)).score) {
            minIdx = i;
        }
    }

    // 5. 결과 출력 (포인터 연산 적용)
    printf("\n--- 전체 학생 성적 리스트 ---\n");
    for (int i = 0; i < N; i++) {
        printf("[%d] 이름: %s | 학번: %d | 성적: %d\n",
                i, (*(students + i)).name, (*(students + i)).id, (*(students + i)).score);
    }

    printf("\n--- 분석 결과 ---\n");
    printf("최고점 학생: %s (학번: %d, 성적: %d)\n",
            (*(students + maxIdx)).name, (*(students + maxIdx)).id, (*(students + maxIdx)).score);
    printf("최저점 학생: %s (학번: %d, 성적: %d)\n",
            (*(students + minIdx)).name, (*(students + minIdx)).id, (*(students + minIdx)).score);
    printf("평균 점수: %.2f\n", (float)sum / N);

    // 6. 메모리 해제
    free(students);

    return 0;
}
