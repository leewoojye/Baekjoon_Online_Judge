#include <stdio.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

static void print_array(const int list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

static int partition_trace(int list[], int left, int right, int n)
{
    int pivot = list[left];
    int low = left;
    int high = right + 1;
    int temp;

    do {
        do {
            low++;
        } while (low <= right && list[low] < pivot);

        do {
            high--;
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            SWAP(list[low], list[high], temp);
        }
    } while (low < high);

    SWAP(list[left], list[high], temp);

    printf("pivot %d -> index %d: ", pivot, high);
    print_array(list, n);
    return high;
}

static void quick_sort_trace(int list[], int left, int right, int n)
{
    if (left < right) {
        int q = partition_trace(list, left, right, n);
        quick_sort_trace(list, left, q - 1, n);
        quick_sort_trace(list, q + 1, right, n);
    }
}

int main(void)
{
    int list[] = { 4, 7, 1, 8, 6, 2, 5, 3 };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    printf("start: ");
    print_array(list, n);
    quick_sort_trace(list, 0, n - 1, n);
    printf("for n=100000, n^2 / (n log2 n) is roughly 100000 / 17, about 5880.\n");
    return 0;
}
