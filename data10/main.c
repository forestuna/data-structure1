#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

int main() {
    sparseMatrix* sm1 = createSparseMatrix(5, 5);
    addElementSparseMatrix(sm1, 2, 1, 10);
    addElementSparseMatrix(sm1, 3, 3, 15);
    addElementSparseMatrix(sm1, 4, 1, 3);

    printf("[sm1 데이터]\n");
    printSparseMatrix(sm1);

    sparseMatrix* sm2 = createSparseMatrix(5, 5);
    addElementSparseMatrix(sm2, 2, 1, 10);
    addElementSparseMatrix(sm2, 3, 4, 15);
    addElementSparseMatrix(sm2, 4, 1, 3);

    printf("\n[sm2 데이터]\n");
    printSparseMatrix(sm2);

    sparseMatrix* sm3 = addSparseMatrix(sm1, sm2);
    
    printf("\n[덧셈(add) 연산 직후 결과]\n"); // 깨진 글자 복구
    printSparseMatrix(sm3);

    // 메모리 누수 방지 (중요!)
    destroyArrayList(sm1);
    destroyArrayList(sm2);
    destroyArrayList(sm3);

    return 0;
}
