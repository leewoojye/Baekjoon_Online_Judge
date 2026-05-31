#include <stdio.h>

static void print_array(const int list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

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

int main(void)
{
    int list[] = { 4, 8, 5, 7, 6, 2, 1, 3 };
    int gaps[] = { 4, 2, 1 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    printf("start : ");
    print_array(list, n);

    for (int g = 0; g < 3; g++) {
        int gap = gaps[g];
        for (int first = 0; first < gap; first++) {
            inc_insertion_sort(list, first, n - 1, gap);
        }
        printf("gap %d : ", gap);
        print_array(list, n);
    }

    printf("growth comparison at n=10000: insertion O(n^2), shell average O(n^1.5).\n");
    printf("The rough growth-factor ratio is sqrt(10000)=100.\n");
    return 0;
}
