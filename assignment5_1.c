#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. n을 입력받는 대신 기호 상수 SIZE를 100으로 정의
#define SIZE 100

int main() {
    // n 대신 SIZE를 사용하므로 n 변수와 scanf가 필요 없습니다.
    int arr[SIZE]; 
    int sum = 0;
    int max, min;

    // 난수 생성을 위한 시드값 설정
    srand((unsigned int)time(NULL));

    // 2. 1 ~ 100 사이의 임의의 수로 배열 채우기
    for (int i = 0; i < SIZE; i++) {
        arr[i] = (rand() % SIZE) + 1;
    }

    // 3. 정방향 출력
    printf("[정방향 출력]:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0) printf("\n"); // 10개마다 줄바꿈 (가독성용)
    }

    // 4. 역방향 출력
    printf("\n[역방향 출력]:\n");
    for (int i = SIZE - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
        if ((SIZE - i) % 10 == 0) printf("\n"); // 10개마다 줄바꿈
    }

    // 5. 총합, 최댓값, 최솟값 계산
    max = arr[0];
    min = arr[0];
    for (int i = 0; i < SIZE; i++) {
        sum += arr[i];
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    printf("\n--- 결과 ---");
    printf("\n배열 크기: %d", SIZE);
    printf("\n총합: %d", sum);
    printf("\n최대값: %d", max);
    printf("\n최소값: %d\n", min);

    return 0;
}
