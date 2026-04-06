#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N;
    int *arr;
    int sum = 0, max, min;

    printf("배열의 크기 N을 입력하세요: ");
    scanf("%d", &N);

    // 1. 동적 할당
    arr = (int *)malloc(sizeof(int) * N);
    if (arr == NULL) return 1;

    srand(time(NULL));

    // 2. 포인터 기법으로 값 채우기
    for (int i = 0; i < N; i++) {
        *(arr + i) = rand() % (N + 1);
    }

    // 3-1. 포인터 기법으로 정방향 출력
    printf("\n[정방향 출력]\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", *(arr + i));
    }

    // 3-2. 포인터 기법으로 역방향 출력
    printf("\n\n[역방향 출력]\n");
    for (int i = N - 1; i >= 0; i--) {
        printf("%d ", *(arr + i));
    }

    // 3-3. 포인터 기법으로 통계 계산
    max = *arr; // 첫 번째 요소
    min = *arr;
    for (int i = 0; i < N; i++) {
        int val = *(arr + i);
        sum += val;
        if (val > max) max = val;
        if (val < min) min = val;
    }

    printf("\n\n[결과 분석]\n");
    printf("총합: %d | 최대값: %d | 최소값: %d\n", sum, max, min);

    free(arr); // 메모리 해제
    return 0;
}
