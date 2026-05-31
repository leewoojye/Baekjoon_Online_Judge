#include <stdio.h>

#define MAX_SIZE 16

static int list[MAX_SIZE] = { 10, 4, 7, 1, 9, 3, 8, 2 };

static int seq_search(int key, int low, int high)
{
    for (int i = low; i <= high; i++) {
        if (list[i] == key) {
            return i;
        }
    }
    return -1;
}

static int seq_search2(int key, int low, int high)
{
    int i;

    list[high + 1] = key;
    for (i = low; list[i] != key; i++) {
        ;
    }

    if (i == high + 1) {
        return -1;
    }
    return i;
}

int main(void)
{
    printf("seq_search(9)=%d\n", seq_search(9, 0, 7));
    printf("seq_search2(5)=%d\n", seq_search2(5, 0, 7));
    return 0;
}
