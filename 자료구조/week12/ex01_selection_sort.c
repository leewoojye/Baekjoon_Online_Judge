#include <stdio.h>

#define MAX_SIZE 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

static void selection_sort(int list[], int n)
{
    int i;
    int j;
    int least;
    int temp;

    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++) {
            if (list[j] < list[least]) {
                least = j;
            }
        }
        SWAP(list[i], list[least], temp);
    }
}

int main(void)
{
    int list[MAX_SIZE] = { 48, 25, 93, 64, 87, 38, 96, 16, 24, 90 };

    selection_sort(list, MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}
