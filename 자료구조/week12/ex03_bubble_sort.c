#include <stdio.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

static void bubble_sort(int list[], int n)
{
    int temp;

    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (list[j] > list[j + 1]) {
                SWAP(list[j], list[j + 1], temp);
            }
        }
    }
}

int main(void)
{
    int list[] = { 3, 7, 4, 1, 6, 9 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    bubble_sort(list, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}
