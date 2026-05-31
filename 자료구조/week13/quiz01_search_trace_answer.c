#include <stdio.h>

static void improved_sequential_trace(void)
{
    int list[9] = { 1, 2, 3, 5, 6, 8, 9, 10, 0 };
    int key = 4;
    int comparisons = 0;
    int i;

    list[8] = key;
    printf("improved sequential search key=4\n");
    for (i = 0; list[i] != key; i++) {
        comparisons++;
        printf("compare index %d value %d\n", i, list[i]);
    }
    comparisons++;
    printf("compare index %d value %d (sentinel)\n", i, list[i]);
    printf("result=-1, comparisons=%d\n\n", comparisons);
}

static void binary_trace(void)
{
    int list[] = { 1, 2, 3, 4, 6, 7, 8, 9 };
    int key = 5;
    int low = 0;
    int high = 7;
    int comparisons = 0;

    printf("binary search key=5\n");
    while (low <= high) {
        int middle = (low + high) / 2;
        comparisons++;
        printf("compare index %d value %d\n", middle, list[middle]);
        if (key == list[middle]) {
            printf("result=%d, comparisons=%d\n\n", middle, comparisons);
            return;
        }
        if (key > list[middle]) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    printf("result=-1, comparisons=%d\n\n", comparisons);
}

static void interpolation_trace(void)
{
    int list[] = { 1, 2, 4, 5, 7, 8, 9, 10 };
    int key = 6;
    int low = 0;
    int high = 7;
    int comparisons = 0;

    printf("interpolation search key=6\n");
    while (list[high] >= key && key > list[low]) {
        int j = (int)(((float)(key - list[low]) / (float)(list[high] - list[low])) * (float)(high - low)) + low;
        comparisons++;
        printf("probe index %d value %d\n", j, list[j]);

        if (key > list[j]) {
            low = j + 1;
        } else if (key < list[j]) {
            high = j - 1;
        } else {
            low = j;
            break;
        }
    }

    comparisons++;
    printf("final check index %d value %d\n", low, list[low]);
    if (list[low] == key) {
        printf("result=%d, comparisons=%d\n", low, comparisons);
    } else {
        printf("result=-1, comparisons=%d\n", comparisons);
    }
}

int main(void)
{
    improved_sequential_trace();
    binary_trace();
    interpolation_trace();
    return 0;
}
