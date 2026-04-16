#include <stdio.h>

/*
 * Pointer parameter example.
 * The slide layout breaks the braces around main(), so this file keeps the same
 * example as a standalone compilable program.
 */
void swap(int *px, int *py)
{
    int tmp;

    tmp = *px;
    *px = *py;
    *py = tmp;
}

int main(void)
{
    int a = 1;
    int b = 2;

    printf("before swap: a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("after swap : a=%d, b=%d\n", a, b);
    return 0;
}
