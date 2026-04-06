#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    int *arr;
    int row, col, num;

    printf("홀수 N을 입력하세요: ");
    scanf("%d", &N);

    if (N % 2 == 0) {
        printf("홀수만 입력 가능합니다.\n");
        return 1;
    }

    // 1. N^2 크기의 배열을 1차원 동적 할당 (포인터 연산 최적화)
    arr = (int *)malloc(sizeof(int) * N * N);
    if (arr == NULL) return 1;

    // 배열을 0으로 초기화
    for (int i = 0; i < N * N; i++) {
        *(arr + i) = 0;
    }

    // 2. 마방진 알고리즘 (Siamese 방법)
    // 첫 번째 숫자인 1을 첫 번째 행의 가운데에 배치
    row = 0;
    col = N / 2;

    for (num = 1; num <= N * N; num++) {
        *(arr + row * N + col) = num; // 포인터 기법으로 값 대입

        // 다음 위치 계산 (한 칸 위, 한 칸 오른쪽)
        int next_row = (row - 1 + N) % N;
        int next_col = (col + 1) % N;

        // 이동하려는 칸에 이미 숫자가 있다면, 현재 칸의 바로 아래로 이동
        if (*(arr + next_row * N + next_col) != 0) {
            row = (row + 1) % N;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    // 3. 배열 전체 출력
    printf("\n[%d x %d 마방진 출력]\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", *(arr + i * N + j));
        }
        printf("\n");
    }

    // 4. 합계 검증 및 출력
    printf("\n[검증 결과]\n");
    int total_sum = 0;

    // 가로 합 계산 (N세트)
    for (int i = 0; i < N; i++) {
        total_sum = 0;
        for (int j = 0; j < N; j++) {
            total_sum += *(arr + i * N + j);
        }
        printf("가로 %d행 합: %d\n", i + 1, total_sum);
    }

    // 세로 합 계산 (N세트)
    for (int j = 0; j < N; j++) {
        total_sum = 0;
        for (int i = 0; i < N; i++) {
            total_sum += *(arr + i * N + j);
        }
        printf("세로 %d열 합: %d\n", j + 1, total_sum);
    }

    // 대각선 합 계산 (우하향)
    total_sum = 0;
    for (int i = 0; i < N; i++) {
        total_sum += *(arr + i * N + i);
    }
    printf("대각선(↘) 합: %d\n", total_sum);

    // 대각선 합 계산 (좌하향)
    total_sum = 0;
    for (int i = 0; i < N; i++) {
        total_sum += *(arr + i * N + (N - 1 - i));
    }
    printf("대각선(↙) 합: %d\n", total_sum);

    // 5. 메모리 해제
    free(arr);

    return 0;
}
