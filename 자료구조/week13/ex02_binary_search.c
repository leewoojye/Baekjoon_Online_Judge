#include <stdio.h>

static int list[] = { 1, 2, 3, 5, 6, 8, 9, 10 };

static int search_binary2(int key, int low, int high)
{
    while (low <= high) {
        int middle = (low + high) / 2;

        if (key == list[middle]) {
            return middle;
        }
        if (key > list[middle]) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return -1;
}

int main(void)
{
    int n = (int)(sizeof(list) / sizeof(list[0]));

    printf("search_binary2(6)=%d\n", search_binary2(6, 0, n - 1));
    printf("search_binary2(7)=%d\n", search_binary2(7, 0, n - 1));
    return 0;
}
