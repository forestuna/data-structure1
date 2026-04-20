#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

// (참고: sparseMatrix는 arrayList의 typedef라고 가정합니다)

sparseMatrix* createSparseMatrix(int row, int col) {
    return createArrayList(row * col);
}

int addElementSparseMatrix(sparseMatrix* sm, int row, int col, int value) {
    int size = sizeArrayList(sm);
    // 삽입 결과를 리턴해주어야 함
    return insertArrayList(sm, size, (elementArrayList) {row, col, value});
}

int printSparseMatrix(sparseMatrix* sm) {
    printf("--- 희소 행렬 출력 ---\n"); // 깨진 글자 복구
    printArrayList(sm);
    return 1; // 리턴값 추가
}

// [오류 수정 1, 2] 인덱스 초과 방지 및 행렬 덧셈 로직 완벽 수정
sparseMatrix* addSparseMatrix(sparseMatrix* sm1, sparseMatrix* sm2) {
    sparseMatrix* smResult = createArrayList(100);
    
    // 1단계: sm1의 모든 원소를 smResult에 그대로 복사
    for (int i = 0; i < sizeArrayList(sm1); i++) { // <= 를 < 로 수정 (인덱스 초과 방지)
        insertArrayList(smResult, sizeArrayList(smResult), getItemArrayList(sm1, i));
    }

    // 2단계: sm2의 원소를 하나씩 보면서 더하거나 새로 추가
    for (int j = 0; j < sizeArrayList(sm2); j++) { // <= 를 < 로 수정
        elementArrayList elemSM2 = getItemArrayList(sm2, j);
        int isMatched = 0; // 매칭 여부 플래그

        // smResult(현재까지 sm1의 데이터)와 비교
        for (int k = 0; k < sizeArrayList(smResult); k++) {
            elementArrayList elemResult = getItemArrayList(smResult, k);

            // 행과 열이 같으면 값을 더해줌
            if (elemResult.row == elemSM2.row && elemResult.col == elemSM2.col) {
                elemResult.value += elemSM2.value;
                replaceItemArrayList(smResult, k, elemResult); // 더한 값으로 갱신
                isMatched = 1;
                break;
            }
        }

        // 만약 sm1과 겹치는 위치가 없었다면 (sm2에만 있는 원소라면) 새롭게 추가
        if (isMatched == 0) {
            insertArrayList(smResult, sizeArrayList(smResult), elemSM2);
        }
    }

    return smResult;
}
