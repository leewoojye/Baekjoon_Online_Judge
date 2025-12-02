#include <stdio.h>

void Min1(int** p, int* a, int* b) {
    *p = (*a < *b) ? a : b;
}

int* Min2(int* a, int* b) {
    return (*a < *b) ? a : b;
}

int main() {
    int a = 10, b = 20;
    int* p1 = NULL;
    int* p2 = NULL;

    Min1(&p1, &a, &b);
    p2 = Min2(&a, &b);

    printf("Min1 result: %d\n", *p1);
    printf("Min2 result: %d\n", *p2);
    return 0;
}