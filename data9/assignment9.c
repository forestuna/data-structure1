#include <stdio.h>
#include <stdlib.h>

// 1. 순차 리스트 구조체 정의
typedef struct {
    int* data;      // 데이터를 저장할 동적 배열
    int capacity;   // 할당된 총 칸 수 (Capacity)
    int size;       // 현재 저장된 데이터 개수 (Size)
} ArrayList;

// 2. 리스트 초기화
void init(ArrayList* list, int init_capacity) {
    list->data = (int*)malloc(sizeof(int) * init_capacity);
    if (list->data == NULL) return; // 메모리 할당 실패 대응

    list->capacity = init_capacity;
    list->size = 0;
    printf("[시스템] 리스트 생성: 초기 용량 %d\n", init_capacity);
}

// 3. 데이터 추가 (포화 상태 시 realloc 수행)
void add(ArrayList* list, int value) {
    // 포화 상태(Full) 확인
    if (list->size == list->capacity) {
        int new_capacity = list->capacity * 2;
        printf("\n[확장] 리스트 포화! 크기 변경: %d -> %d\n", list->capacity, new_capacity);
        
        // realloc을 통한 메모리 재할당
        int* temp = (int*)realloc(list->data, sizeof(int) * new_capacity);
        
        if (temp == NULL) {
            printf("[오류] 메모리 재할당 실패!\n");
            return;
        }
        
        list->data = temp;
        list->capacity = new_capacity;
    }

    // 데이터 삽입
    list->data[list->size] = value;
    list->size++;
    printf("추가: %2d | 상태: (%d/%d)\n", value, list->size, list->capacity);
}

// 4. 리스트 출력
void display(ArrayList* list) {
    if (list->size == 0) {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    printf("\n--- 현재 리스트 데이터 ---\n");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n------------------------\n");
}

// 5. 메모리 해제
void clear(ArrayList* list) {
    if (list->data != NULL) {
        free(list->data);
        list->data = NULL;
    }
    list->size = list->capacity = 0;
    printf("\n[시스템] 메모리가 해제되었습니다.\n");
}

int main() {
    ArrayList list;
    
    // 초기 용량 2로 시작하여 확장을 테스트
    init(&list, 2); 

    add(&list, 10);
    add(&list, 20);
    
    // 이 시점에서 포화 발생 -> 4로 확장
    add(&list, 30); 
    add(&list, 40);
    
    // 이 시점에서 포화 발생 -> 8로 확장
    add(&list, 50);

    display(&list);

    clear(&list);
    return 0;
}
