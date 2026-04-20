#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;      
    int capacity;   
    int size;       
} ArrayList;

void init(ArrayList* list, int init_capacity) {
    list->data = (int*)malloc(sizeof(int) * init_capacity);
    if (list->data == NULL) return;
    list->capacity = init_capacity;
    list->size = 0;
}

// 1. 특정 위치에 추가 (Insert)
void insert(ArrayList* list, int pos, int value) {
    if (value <= 0) {
        printf("[오류] 양의 정수만 입력 가능합니다.\n");
        return;
    }
    if (pos < 0 || pos > list->size) {
        printf("[오류] 유효하지 않은 위치입니다. (가능 범위: 0 ~ %d)\n", list->size);
        return;
    }
    
    // 포화 상태 시 확장
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (int*)realloc(list->data, sizeof(int) * list->capacity);
    }

    // pos 위치를 비우기 위해 데이터 오른쪽으로 이동
    for (int i = list->size; i > pos; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[pos] = value;
    list->size++;
    printf(">> 위치 %d에 값 %d 삽입 완료\n", pos, value);
}

// 2. 특정 위치 삭제 (Delete)
void delete_item(ArrayList* list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("[오류] 유효하지 않은 위치입니다.\n");
        return;
    }
    int del_val = list->data[pos];
    
    // 데이터를 왼쪽으로 이동시켜 삭제
    for (int i = pos; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
    printf(">> 위치 %d의 값 %d 삭제 완료\n", pos, del_val);
}

// 3. 특정 위치 값 변경 (Replace)
void replace(ArrayList* list, int pos, int value) {
    if (value <= 0) {
        printf("[오류] 양의 정수만 입력 가능합니다.\n");
        return;
    }
    if (pos < 0 || pos >= list->size) {
        printf("[오류] 유효하지 않은 위치입니다.\n");
        return;
    }
    list->data[pos] = value;
    printf(">> 위치 %d의 값을 %d(으)로 변경 완료\n", pos, value);
}

// 4. 위치와 함께 출력 (Print)
void print_list(ArrayList* list) {
    printf("\n--- 현재 순차 리스트 (크기: %d/%d) ---\n", list->size, list->capacity);
    if (list->size == 0) {
        printf("리스트가 비어있습니다.\n");
        return;
    }
    for (int i = 0; i < list->size; i++) {
        printf("[위치 %d] : %d\n", i, list->data[i]);
    }
    printf("------------------------------------\n");
}

// 5. 전체 삭제 (Clear)
void clear_list(ArrayList* list) {
    list->size = 0; // 메모리 해제 없이 논리적 삭제 (재사용을 위함)
    printf(">> 리스트의 모든 값을 삭제했습니다.\n");
}

int main() {
    ArrayList list;
    init(&list, 2);
    int choice, pos, val;

    while (1) {
        printf("\n[ 메뉴 ] 1.추가(Insert) 2.삭제(Delete) 3.변경(Replace) 4.출력(Print) 5.초기화(Clear) 0.종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        switch (choice) {
            case 1:
                printf("추가할 위치와 양의 정수 입력 (예: 0 50): ");
                scanf("%d %d", &pos, &val);
                insert(&list, pos, val);
                break;
            case 2:
                printf("삭제할 위치 입력: ");
                scanf("%d", &pos);
                delete_item(&list, pos);
                break;
            case 3:
                printf("변경할 위치와 양의 정수 입력: ");
                scanf("%d %d", &pos, &val);
                replace(&list, pos, val);
                break;
            case 4:
                print_list(&list);
                break;
            case 5:
                clear_list(&list);
                break;
            기본:
                printf("잘못된 입력입니다.\n");
        }
    }
    free(list.data);
    return 0;
}
