#include <stdio.h>
#include <stdlib.h>

void generateMagicSquare(int n) {
    // 2차원 배열 동적 할당 및 0으로 초기화
    int** magicSquare = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        magicSquare[i] = (int*)calloc(n, sizeof(int));
    }

    int row = 0;          // 첫 번째 행
    int col = n / 2;      // 가운데 열
    int num = 1;

    while (num <= n * n) {
        magicSquare[row][col] = num++;

        // 다음 위치 계산 (오른쪽 위로 이동)
        int nextRow = (row - 1 < 0) ? n - 1 : row - 1;
        int nextCol = (col + 1 >= n) ? 0 : col + 1;

        // 이미 숫자가 채워져 있다면 현재 위치의 바로 아래 행으로 이동
        if (magicSquare[nextRow][nextCol] != 0) {
            row = (row + 1 >= n) ? 0 : row + 1;
        }
        else {
            row = nextRow;
            col = nextCol;
        }
    }

    // 결과 출력
    printf("%d x %d 마방진 결과:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", magicSquare[i][j]);
        }
        printf("\n");
    }

    // 메모리 해제
    for (int i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);
}

int main() {
    int n;

    printf("홀수 n을 입력하세요: ");
    scanf_s("%d", &n);

    if (n % 2 == 0 || n <= 0) {
        printf("홀수만 입력 가능합니다.\n");
        return 1;
    }

    generateMagicSquare(n);

    return 0;
}
