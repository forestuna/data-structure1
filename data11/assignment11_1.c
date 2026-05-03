#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 100 // 순차 리스트 최대 크기

// 단일 항 구조체
typedef struct {
    int coef; // 계수
    int exp;  // 지수
} Term;

// 다항식 순차 리스트 구조체
typedef struct {
    Term terms[MAX_TERMS];
    int size; // 현재 항의 개수
} Polynomial;

// 다항식 초기화
void initPoly(Polynomial* p) {
    p->size = 0;
}

// 다항식에 새로운 항 추가 (같은 지수가 있으면 계수를 더함, 지수 내림차순 정렬)
void addTerm(Polynomial* p, int coef, int exp) {
    if (coef == 0) return; // 계수가 0이면 무시

    // 1. 이미 같은 지수를 가진 항이 있는지 검색
    for (int i = 0; i < p->size; i++) {
        if (p->terms[i].exp == exp) {
            p->terms[i].coef += coef;
            return;
        }
    }

    // 2. 같은 지수가 없다면 지수 내림차순으로 삽입 위치 찾기
    int pos = p->size;
    while (pos > 0 && p->terms[pos - 1].exp < exp) {
        p->terms[pos] = p->terms[pos - 1]; // 뒤로 밀기
        pos--;
    }

    // 3. 삽입
    p->terms[pos].coef = coef;
    p->terms[pos].exp = exp;
    p->size++;
}

// 문자열을 다항식 리스트로 파싱 (예: 3X^2+2X^1+1X^0)
void parsePoly(char* str, Polynomial* p) {
    initPoly(p);
    // '+' 문자를 기준으로 문자열 자르기
    char* token = strtok(str, "+");
    while (token != NULL) {
        int coef = 0, exp = 0;
        // X^ 를 기준으로 계수와 지수 추출
        if (sscanf(token, "%dX^%d", &coef, &exp) == 2) {
            addTerm(p, coef, exp);
        }
        token = strtok(NULL, "+");
    }
}

// 두 다항식 덧셈
Polynomial addPoly(Polynomial* a, Polynomial* b) {
    Polynomial result;
    initPoly(&result);
    
    for (int i = 0; i < a->size; i++) addTerm(&result, a->terms[i].coef, a->terms[i].exp);
    for (int i = 0; i < b->size; i++) addTerm(&result, b->terms[i].coef, b->terms[i].exp);
    
    return result;
}

// 두 다항식 곱셈
Polynomial multiplyPoly(Polynomial* a, Polynomial* b) {
    Polynomial result;
    initPoly(&result);

    for (int i = 0; i < a->size; i++) {
        for (int j = 0; j < b->size; j++) {
            int newCoef = a->terms[i].coef * b->terms[j].coef;
            int newExp = a->terms[i].exp + b->terms[j].exp;
            addTerm(&result, newCoef, newExp);
        }
    }
    return result;
}

// 다항식 출력
void printPoly(Polynomial* p) {
    if (p->size == 0) {
        printf("0\n");
        return;
    }
    for (int i = 0; i < p->size; i++) {
        printf("%dX^%d", p->terms[i].coef, p->terms[i].exp);
        if (i < p->size - 1) printf(" + ");
    }
    printf("\n");
}

int main() {
    Polynomial p1, p2, sum, product;
    char input1[100], input2[100];

    printf("첫 번째 다항식 입력 (예: 3X^2+2X^1+1X^0): ");
    scanf("%s", input1);
    parsePoly(input1, &p1);

    printf("두 번째 다항식 입력: ");
    scanf("%s", input2);
    parsePoly(input2, &p2);

    sum = addPoly(&p1, &p2);
    product = multiplyPoly(&p1, &p2);

    printf("\n[덧셈 결과] : ");
    printPoly(&sum);

    printf("[곱셈 결과] : ");
    printPoly(&product);

    return 0;
}
