#include <stdio.h>
#include <stdlib.h>

// 순차 리스트 구조체 정의
typedef struct {
    int* data;      // 데이터를 저장할 동적 배열
    int capacity;   // 현재 할당된 총 칸 수 (용량)
    int size;       // 현재 저장된 데이터 개수
} ArrayList;

// 리스트 초기화 함수
void init(ArrayList* list, int init_capacity) {
    list->data = (int*)malloc(sizeof(int) * init_capacity);
    list->capacity = init_capacity;
    list->size = 0;
    printf("리스트 생성: 초기 용량 %d\n", init_capacity);
}

// 리스트에 데이터 추가 (포화 상태 시 realloc 수행)
void add(ArrayList* list, int value) {
    // 1. 포화 상태인지 확인
    if (list->size == list->capacity) {
        printf("\n[경고] 포화 상태 발생! 크기를 늘립니다. (%d -> %d)\n", list->capacity, list->capacity * 2);
        
        // 2. realloc을 사용하여 크기를 2배로 확장
        int* temp = (int*)realloc(list->data, sizeof(int) * list->capacity * 2);
        
        // realloc 실패 대응 (메모리 부족 시)
        if (temp == NULL) {
            printf("메모리 재할당 실패!\n");
            return;
        }
        
        list->data = temp;
        list->capacity *= 2;
    }

    // 3. 데이터 삽입
    list->data[list->size] = value;
    list->size++;
    printf("데이터 추가: %d (현재 크기: %d/%d)\n", value, list->size, list->capacity);
}

// 리스트 전체 출력
void display(ArrayList* list) {
    printf("현재 리스트: ");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// 메모리 해제
void clear(ArrayList* list) {
    free(list->data);
    list->data = NULL;
    list->size = list->capacity = 0;
}

int main() {
    ArrayList myList;
    init(&myList, 3); // 처음에 작은 크기(3)로 시작

    add(&myList, 10);
    add(&myList, 20);
    add(&myList, 30);
    
    // 여기서 포화 상태 발생 및 realloc 호출
    add(&myList, 40); 
    add(&myList, 50);

    display(&myList);

    clear(&myList);
    return 0;
}
