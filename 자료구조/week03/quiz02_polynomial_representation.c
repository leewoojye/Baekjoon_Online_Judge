/*
Quiz
1. 다항식 6x^3 + 8x^2 + 9를 첫번째 방법으로 표현하여라.
2. 다항식 6x^3 + 8x^2 + 9를 두번째 방법으로 표현하여라.
3. 첫번째 방법으로 뺄셈을 구현하려면 덧셈 코드의 어떤 부분을 변경하면 되는가?
4. 첫번째 방법으로 특정한 x값에서 다항식의 값을 계산하는 함수 poly_eval(int x)를 작성해 보자.

예시 답안
1. 첫번째 방법(계수 배열):
   degree = 3
   coef = {6, 8, 0, 9}
2. 두번째 방법(0이 아닌 항만 저장):
   {(6, 3), (8, 2), (9, 0)}
3. A - B를 구현하려면
   - 같은 차수의 항은 A.coef - B.coef 로 계산하고
   - B 쪽 항이 더 큰 차수일 때는 계수를 음수로 넣으면 된다.
4. poly_eval은 Horner 방식으로 구현할 수 있다.
*/

#include <stdio.h>

#define MAX_DEGREE 101
#define MAX_TERMS 101
#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct {
    int degree;
    float coef[MAX_DEGREE];
} PolynomialArray;

typedef struct {
    float coef;
    int expon;
} Term;

PolynomialArray poly_sub1(PolynomialArray A, PolynomialArray B)
{
    PolynomialArray C = {0, {0}};
    int Apos = 0;
    int Bpos = 0;
    int Cpos = 0;
    int degree_a = A.degree;
    int degree_b = B.degree;

    C.degree = max(A.degree, B.degree);
    while (Apos <= A.degree && Bpos <= B.degree) {
        if (degree_a > degree_b) {
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        } else if (degree_a == degree_b) {
            C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
            degree_a--;
            degree_b--;
        } else {
            C.coef[Cpos++] = -B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

float poly_eval(PolynomialArray p, int x)
{
    float result = p.coef[0];

    for (int i = 1; i <= p.degree; i++) {
        result = result * x + p.coef[i];
    }
    return result;
}

void print_poly_array(PolynomialArray p)
{
    for (int i = p.degree; i > 0; i--) {
        printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
    }
    printf("%3.1f\n", p.coef[p.degree]);
}

void print_term_array(Term terms[], int count)
{
    for (int i = 0; i < count; i++) {
        printf("(%3.1f, %d)", terms[i].coef, terms[i].expon);
        if (i + 1 < count) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void)
{
    PolynomialArray p = {3, {6, 8, 0, 9}};
    PolynomialArray q = {3, {1, 2, 3, 4}};
    PolynomialArray diff;
    Term sparse_terms[MAX_TERMS] = {
        {6, 3},
        {8, 2},
        {9, 0},
    };

    printf("Dense representation:\n");
    print_poly_array(p);

    printf("Sparse representation:\n");
    print_term_array(sparse_terms, 3);

    diff = poly_sub1(p, q);
    printf("Subtraction example p - q:\n");
    print_poly_array(diff);

    printf("p(2) = %.1f\n", poly_eval(p, 2));
    return 0;
}
