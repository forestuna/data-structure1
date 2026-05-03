#include <stdio.h>
#include <stdlib.h>

struct pointType {
    int x;
    int y;
    struct pointType* next;
};

struct linkedList {
    struct pointType* head;
    int size;
};

struct linkedList* createLinkedList();
int destroyLinkedList(struct linkedList* li);

int main() {
    struct linkedList* myList1;
    myList1 = createLinkedList();

    // 첫 번째 노드 생성
    struct pointType* nptr;
    nptr = (struct pointType*)malloc(sizeof(struct pointType));
    nptr->x = 10;
    nptr->y = 20;
    nptr->next = (struct pointType*)NULL;

    myList1->head = nptr;
    myList1->size++; // [오류 수정] 노드 추가 시 사이즈 증가

    // 포인터 출력은 %x 대신 %p를 사용하는 것이 안전합니다.
    printf("myList1: head: %p, size: %d\n", (void*)myList1->head, myList1->size);
    printf("first node: x: %d, y: %d, next: %p\n\n", 
           myList1->head->x, myList1->head->y, (void*)myList1->head->next);

    // 두 번째 노드 생성 및 헤드 교체 (앞에 삽입)
    nptr = (struct pointType*)malloc(sizeof(struct pointType));
    nptr->x = 20;
    nptr->y = 30;
    nptr->next = myList1->head;
    myList1->head = nptr;
    myList1->size++; // [오류 수정] 노드 추가 시 사이즈 증가

    printf("new first node: x: %d, y: %d, next: %p\n", 
           myList1->head->x, myList1->head->y, (void*)myList1->head->next);
    printf("myList1 size updated: %d\n\n", myList1->size);

    // 전체 리스트 순회 출력
    for (nptr = myList1->head; nptr != NULL; nptr = nptr->next) {
        printf("node: x: %d, y: %d, next: %p\n", nptr->x, nptr->y, (void*)nptr->next);
    }

    destroyLinkedList(myList1);
    
    return 0; // [오류 수정] main 함수 정상 종료 반환
}

struct linkedList* createLinkedList() {
    struct linkedList* r;
    r = (struct linkedList*)malloc(sizeof(struct linkedList));

    r->head = (struct pointType*)NULL;
    r->size = 0;

    return r;
}

int destroyLinkedList(struct linkedList* li) {
    struct pointType* nptr, * mptr;
    for (nptr = li->head; nptr != NULL; nptr = mptr) {
        mptr = nptr->next;
        free(nptr);
    }

    free(li);

    return 1;
}
