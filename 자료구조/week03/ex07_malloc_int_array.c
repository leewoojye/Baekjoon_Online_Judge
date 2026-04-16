#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int main(void)
{
    int *p;

    p = (int *)malloc(SIZE * sizeof(int));
    if (p == NULL) {
        fprintf(stderr, "Not enough memory.\n");
        exit(1);
    }

    for (int i = 0; i < SIZE; i++) {
        p[i] = i;
    }
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");

    free(p);
    return 0;
}
