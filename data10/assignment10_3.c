#include <stdio.h>
#include <stdlib.h>
#include "arrayList.h"

// (참고: arrayList.h 안에 elementArrayList와 arrayList 구조체가 선언되어 있어야 합니다.)

arrayList* createArrayList(int size) {
    arrayList* al = (arrayList*)malloc(sizeof(arrayList));
    al->data = (elementArrayList*)malloc(sizeof(elementArrayList) * size);
    al->size = 0;
    al->capacity = size;
    return al;
}

void destroyArrayList(arrayList* al) {
    free(al->data);
    free(al);
}

int isEmptyArrayList(arrayList* al) {
    return (al->size == 0) ? 1 : 0;
}

int isFullArrayList(arrayList* al) {
    return (al->size == al->capacity) ? 1 : 0;
}

int sizeArrayList(arrayList* al) {
    return al->size;
}

// [오류 수정 1] 포화 검사 추가 및 메모리 침범(Out-of-bounds) 루프 수정
int insertArrayList(arrayList* al, int pos, elementArrayList item) {
    // 1. 포화 상태이거나 유효하지 않은 위치면 실패
    if (isFullArrayList(al) || pos < 0 || pos > al->size) {
        return 0; 
    }

    // 2. 루프의 시작을 size - 1 부터 하여 메모리 침범 방지
    for (int i = al->size - 1; i >= pos; i--) {
        al->data[i + 1] = al->data[i];
    }

    al->data[pos] = item;
    al->size++;

    return 1;
}

// [오류 수정 2] 삭제 예외 처리 (빈 껍데기 if문 수정)
elementArrayList deleteArrayList(arrayList* al, int pos) {
    // 범위 초과 시 에러 값을 가진 임시 구조체 반환
    if (pos < 0 || pos >= al->size) {
        elementArrayList errorItem = {-1, -1, -1}; // 에러 식별용 더미 데이터
        printf("[오류] 삭제할 수 없는 위치입니다.\n");
        return errorItem;
    }

    elementArrayList item = al->data[pos];

    for (int i = pos; i < al->size - 1; i++) {
        al->data[i] = al->data[i + 1];
    }

    al->size--;

    return item;
}

// [오류 수정 3] O(1) 초기화 성능 개선 및 리턴값 추가
int initArrayList(arrayList* al) {
    // 하나씩 지울 필요 없이 논리적 사이즈만 0으로 초기화하면 됨
    al->size = 0; 
    return 1; // 성공 반환
}

elementArrayList getItemArrayList(arrayList* al, int pos) {
    // 여기도 안전을 위해 예외 처리 추가 가능
    if (pos < 0 || pos >= al->size) {
        elementArrayList errorItem = {-1, -1, -1};
        return errorItem;
    }
    return al->data[pos];
}

int replaceItemArrayList(arrayList* al, int pos, elementArrayList item) {
    // 기존 코드에 있던 size - 1 은 size >= 1일 때만 유효. 명확하게 변경.
    if (pos < 0 || pos >= al->size) {
        return 0;
    }

    al->data[pos] = item;
    return 1;
}

// [오류 수정 4] 깨진 문자열 복구
void printArrayList(arrayList* al) {
    printf("희소 행렬 순차 리스트: ");
    printf("Cap: %d, size: %d\n", al->capacity, al->size);

    for (int i = 0; i < al->size; i++) {
        printf("(%d %d %d) ", al->data[i].row, al->data[i].col, al->data[i].value);
    }
    printf("\n");
}
