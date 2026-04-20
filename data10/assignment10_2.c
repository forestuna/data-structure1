#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 행렬의 원소(Term) 구조체
typedef struct {
    int row;
    int col;
    int value;
} Term;

// 원소를 담는 순차 리스트 구조체
typedef struct {
    Term* data;
    int capacity;
    int size;
} ArrayList;

// 희소행렬 구조체 (요구사항 반영: 여러 단계 포인터)
typedef struct {
    int rows;
    int cols;
    ArrayList* list; // 다중 포인터 접근: matrix->list->data[i]
} SparseMatrix;

// 1. 희소 행렬 생성 (이중 포인터/동적 할당 활용)
SparseMatrix* createSparseMatrix(int r, int c, int cap) {
    SparseMatrix* sm = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    sm->rows = r;
    sm->cols = c;
    sm->list = (ArrayList*)malloc(sizeof(ArrayList));
    sm->list->data = (Term*)malloc(sizeof(Term) * cap);
    sm->list->capacity = cap;
    sm->list->size = 0;
    return sm;
}

// 2. 값 삽입
void addTerm(SparseMatrix* sm, int r, int c, int v) {
    ArrayList* lst = sm->list;
    if (lst->size == lst->capacity) {
        lst->capacity *= 2;
        lst->data = (Term*)realloc(lst->data, sizeof(Term) * lst->capacity);
    }
    lst->data[lst->size].row = r;
    lst->data[lst->size].col = c;
    lst->data[lst->size].value = v;
    lst->size++;
}

// 3. Fast Transpose (빠른 전치 행렬 알고리즘 적용)
SparseMatrix* fastTranspose(SparseMatrix* a) {
    // a의 전치이므로 크기는 (cols x rows)
    SparseMatrix* b = createSparseMatrix(a->cols, a->rows, a->list->capacity);
    int numTerms = a->list->size;
    b->list->size = numTerms;

    if (numTerms > 0) {
        int* rowTerms = (int*)calloc(a->cols, sizeof(int));
        int* startingPos = (int*)calloc(a->cols, sizeof(int));

        // 각 열(전치 후의 행)에 원소가 몇 개 있는지 계산
        for (int i = 0; i < numTerms; i++) {
            rowTerms[a->list->data[i].col]++;
        }

        // 시작 위치 계산
        startingPos[0] = 0;
        for (int i = 1; i < a->cols; i++) {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }

        int moveCount = 0; // 데이터 이동 횟수 카운트
        for (int i = 0; i < numTerms; i++) {
            int j = startingPos[a->list->data[i].col]++; // 들어갈 위치 
            
            b->list->data[j].row = a->list->data[i].col;
            b->list->data[j].col = a->list->data[i].row;
            b->list->data[j].value = a->list->data[i].value;
            moveCount++; // 데이터 이동 1회 발생
        }
        
        printf("\n=> [전치 행렬 변환 완료] 데이터 이동 횟수: %d번\n", moveCount);
        free(rowTerms);
        free(startingPos);
    }
    return b;
}

// 4. 출력용 함수
void printMatrix(SparseMatrix* sm, const char* name) {
    printf("\n--- %s (크기: %dx%d, 원소: %d개) ---\n", name, sm->rows, sm->cols, sm->list->size);
    printf("Row\tCol\tValue\n");
    for (int i = 0; i < sm->list->size; i++) {
        printf("%d\t%d\t%d\n", sm->list->data[i].row, sm->list->data[i].col, sm->list->data[i].value);
    }
}

int main() {
    srand((unsigned int)time(NULL));
    
    // 10x10 행렬 생성 (초기 용량 20)
    SparseMatrix* sm = createSparseMatrix(10, 10, 20);

    // 0이 아닌 원소 20개 초기화 (랜덤 삽입, 중복 처리 로직 생략하고 단순 삽입)
    for (int i = 0; i < 20; i++) {
        // 정렬된 순서대로 넣기 위해 행을 i/2 로 단순화 (0~9행까지)
        int r = i / 2;  
        int c = rand() % 10;
        int v = (rand() % 99) + 1;
        addTerm(sm, r, c, v);
    }

    printMatrix(sm, "원본 희소 행렬 (A)");

    // 전치행렬 수행
    SparseMatrix* sm_trans = fastTranspose(sm);

    printMatrix(sm_trans, "전치 희소 행렬 (A^T)");

    // 메모리 해제
    free(sm->list->data); free(sm->list); free(sm);
    free(sm_trans->list->data); free(sm_trans->list); free(sm_trans);

    return 0;
}
