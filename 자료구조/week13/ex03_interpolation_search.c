#include <stdio.h>

static int list[] = { 1, 2, 4, 5, 7, 8, 9, 10 };

static int interpol_search(int key, int n)
{
    int low = 0;
    int high = n - 1;
    int j;

    while (list[high] >= key && key > list[low]) {
        j = (int)(((float)(key - list[low]) / (float)(list[high] - list[low])) * (float)(high - low)) + low;

        if (key > list[j]) {
            low = j + 1;
        } else if (key < list[j]) {
            high = j - 1;
        } else {
            low = j;
        }
    }

    if (list[low] == key) {
        return low;
    }
    return -1;
}

int main(void)
{
    int n = (int)(sizeof(list) / sizeof(list[0]));

    printf("interpol_search(7)=%d\n", interpol_search(7, n));
    printf("interpol_search(6)=%d\n", interpol_search(6, n));
    return 0;
}
