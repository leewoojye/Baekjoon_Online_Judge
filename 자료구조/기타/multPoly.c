#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 101

typedef struct {
    float coef;
    int xpow;
    int ypow;
    int zpow;
} Term;

typedef struct {
    Term terms[MAX_TERMS];
    int term_count;
} Polynomial;

// y 내림차순 조건 유지하는 비교함수
// qsort + compare_terms 조합은 비교 함수의 반환 값이 0보다 크면 b를 a보다 앞에 위치시킴
// const void*는 어떤 타입이든 가리킬 수 있지만, 그 포인터를 통해 가리키는 대상의 내용을 변경할 수는 없는 범용 포인터
int compare_terms(const void* a, const void* b) {
    Term* term_a = (Term*)a;
    Term* term_b = (Term*)b;
    
    // y 차수를 가장 먼저 비교함으로써 y에 대한 내림차순을 구현함
    if (term_b->ypow != term_a->ypow)
        return term_b->ypow - term_a->ypow;
    if (term_b->xpow != term_a->xpow)
        return term_b->xpow - term_a->xpow;
    if (term_b->zpow != term_a->zpow)
        return term_b->zpow - term_a->zpow;
    return 0;
}

// 다항식 초기화
Polynomial create_polynomial() {
    Polynomial p;
    p.term_count = 0;
    return p;
}

// 항 추가
void add_term(Polynomial* p, float coef, int xpow, int ypow, int zpow) {
    if (p->term_count < MAX_TERMS) {
        p->terms[p->term_count].coef = coef;
        p->terms[p->term_count].xpow = xpow;
        p->terms[p->term_count].ypow = ypow;
        p->terms[p->term_count].zpow = zpow;
        p->term_count++;
    }
}

// 한 다항식 내에서 차수가 같은 항은 합침
// 파이프라인 : 한 다항식 내에 y를 기준으로 qsort()로 내림차순 정렬 -> 정렬된 다항식 첫 항부터 순회하며 인접한 항이 같은 차수면 합침
Polynomial combine_terms(Polynomial p) {
    if (p.term_count == 0) return p;
    
    // qsort()
    // p.terms는 정렬하고자 하는 배열의 시작 주소를 나타냄
    // p.term_count는 Polynomial 구조체 p가 현재 가지고 있는 항의 총개수를 나타냅니다. 즉, 배열에서 몇 개의 요소를 정렬할지 알려줍니다.
    // sizeof(Term)은 Term 구조체 하나가 메모리에서 차지하는 크기를 계산합니다. qsort 함수는 이 정보를 바탕으로 배열의 다음 요소로 정확하게 이동할 수 있습니다.
    qsort(p.terms, p.term_count, sizeof(Term), compare_terms);
    
    Polynomial result = create_polynomial();
    
    float current_coef = p.terms[0].coef;
    int current_x = p.terms[0].xpow;
    int current_y = p.terms[0].ypow;
    int current_z = p.terms[0].zpow;
    
    for (int i = 1; i < p.term_count; i++) {
        if (p.terms[i].xpow == current_x && 
            p.terms[i].ypow == current_y && 
            p.terms[i].zpow == current_z) {
            current_coef += p.terms[i].coef;
        } else {
            if (current_coef != 0) {
                add_term(&result, current_coef, current_x, current_y, current_z);
            }
            current_coef = p.terms[i].coef;
            current_x = p.terms[i].xpow;
            current_y = p.terms[i].ypow;
            current_z = p.terms[i].zpow;
        }
    }
    if (current_coef != 0) {
        add_term(&result, current_coef, current_x, current_y, current_z);
    }
    
    return result;
}

// 두 다항식의 곱셈
Polynomial multPoly(Polynomial A, Polynomial B) {
    Polynomial C = create_polynomial();
    
    for (int i = 0; i < A.term_count; i++) {
        for (int j = 0; j < B.term_count; j++) {
            float new_coef = A.terms[i].coef * B.terms[j].coef;
            int new_x = A.terms[i].xpow + B.terms[j].xpow;
            int new_y = A.terms[i].ypow + B.terms[j].ypow;
            int new_z = A.terms[i].zpow + B.terms[j].zpow;
            add_term(&C, new_coef, new_x, new_y, new_z);
        }
    }
    
    return combine_terms(C);
}

// 출력함수
void print_poly(Polynomial p) {
    if (p.term_count == 0) {
        printf("0\n");
        return;
    }
    
    for (int i = 0; i < p.term_count; i++) {
        if (i > 0 && p.terms[i].coef >= 0) printf(" + ");
        
        printf("%.0f", p.terms[i].coef);
        
        int var_count = 0; 
        
        if (p.terms[i].ypow > 0) {
            if (var_count > 0) printf("*");
            printf("y");
            if (p.terms[i].ypow > 1) printf("^%d", p.terms[i].ypow);
            var_count++;
        }
        if (p.terms[i].xpow > 0) {
            if (var_count > 0) printf("*");
            printf("x");
            if (p.terms[i].xpow > 1) printf("^%d", p.terms[i].xpow);
            var_count++;
        }
        if (p.terms[i].zpow > 0) {
            if (var_count > 0) printf("*");
            printf("z");
            if (p.terms[i].zpow > 1) printf("^%d", p.terms[i].zpow);
            var_count++;
        }
    }
    printf("\n");
}

int main() {
    printf("test case\n");
    Polynomial a1 = create_polynomial();
    add_term(&a1, 3, 0, 7, 0);      
    add_term(&a1, 4, 4, 0, 0);      
    add_term(&a1, -1, 0, 0, 0);     
    
    Polynomial b1 = create_polynomial();
    add_term(&b1, 5, 4, 0, 0);      
    add_term(&b1, -3, 0, 2, 0);     
    add_term(&b1, 7, 0, 0, 0);      
    
    printf("A: ");
    print_poly(a1);
    printf("B: ");
    print_poly(b1);
    Polynomial c1 = multPoly(a1, b1);
    printf("A*B: ");
    print_poly(c1);
    printf("\n");
    
    printf("general case\n");
    Polynomial a2 = create_polynomial();
    add_term(&a2, 4, 0, 7, 0);      
    add_term(&a2, -4, 4, 0, 0);     
    add_term(&a2, -1, 0, 0, 0);     
    
    Polynomial b2 = create_polynomial();
    add_term(&b2, 2, 0, 7, 0);     
    add_term(&b2, -3, 1, 0, 0);    
    add_term(&b2, 1, 0, 0, 0);   
    
    printf("A: ");
    print_poly(a2);
    printf("B: ");
    print_poly(b2);
    Polynomial c2 = multPoly(a2, b2);
    printf("A*B: ");
    print_poly(c2);
    printf("\n");
    
    printf("extreme case\n");
    Polynomial a3 = create_polynomial();
    add_term(&a3, 15, 4, 7, 0);     
    add_term(&a3, -9, 0, 9, 0);   
    add_term(&a3, 21, 0, 7, 0);  
    add_term(&a3, 20, 8, 0, 0);     
    
    Polynomial b3 = create_polynomial();
    add_term(&b3, -12, 4, 2, 0);   
    add_term(&b3, 23, 4, 0, 0);     
    add_term(&b3, 3, 0, 2, 0);    
    add_term(&b3, -7, 0, 0, 0);   
    
    printf("A: ");
    print_poly(a3);
    printf("B: ");
    print_poly(b3);
    Polynomial c3 = multPoly(a3, b3);
    printf("A*B: ");
    print_poly(c3);
    printf("\n");
    
    printf("extreme case2\n");
    Polynomial a4 = create_polynomial();
    add_term(&a4, 15, 4, 7, 3);     
    add_term(&a4, -9, 0, 9, 2);  
    add_term(&a4, 21, 0, 7, 0);   
    add_term(&a4, 20, 8, 0, 0);     
    
    Polynomial b4 = create_polynomial();
    add_term(&b4, -12, 4, 2, 2);    
    add_term(&b4, 23, 4, 0, 0);    
    add_term(&b4, 3, 0, 2, 0);     
    add_term(&b4, -7, 0, 0, 0); 
    
    printf("A: ");
    print_poly(a4);
    printf("B: ");
    print_poly(b4);
    Polynomial c4 = multPoly(a4, b4);
    printf("A*B: ");
    print_poly(c4);
    printf("\n");
    
    return 0;
}
