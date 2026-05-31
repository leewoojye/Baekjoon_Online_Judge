#include <stdio.h>

static void insertion_sort(int list[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = list[i];
        int j;

        for (j = i - 1; j >= 0 && list[j] > key; j--) {
            list[j + 1] = list[j];
        }
        list[j + 1] = key;
    }
}

int main(void)
{
    int list[] = { 9, 3, 7, 4, 1, 6 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    insertion_sort(list, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}
