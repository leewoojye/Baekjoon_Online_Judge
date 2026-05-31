#include <stdio.h>

static void inc_insertion_sort(int list[], int first, int last, int gap)
{
    for (int i = first + gap; i <= last; i += gap) {
        int key = list[i];
        int j;

        for (j = i - gap; j >= first && key < list[j]; j -= gap) {
            list[j + gap] = list[j];
        }
        list[j + gap] = key;
    }
}

static void shell_sort(int list[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) {
        if (gap % 2 == 0) {
            gap++;
        }
        for (int i = 0; i < gap; i++) {
            inc_insertion_sort(list, i, n - 1, gap);
        }
    }
}

int main(void)
{
    int list[] = { 4, 8, 5, 7, 6, 2, 1, 3 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    shell_sort(list, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}
