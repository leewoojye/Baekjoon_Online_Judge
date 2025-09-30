#include <stdio.h>
#define SIZE 10

int main()
{
    int a[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, even[SIZE], odd[SIZE], i, j, k;

    // a[i], even[j], odd[k]
    for (i = j = k = 0; i < SIZE; i++) {
        if (a[i] % 2 == 0) // if even, store in even array
            even[j++] = a[i];
        else // if odd, store in odd array
            odd[k++] = a[i]; // 채워야 할 부분
    }

    // print even array
    printf("even = ");
    for (i = 0; i < j; i++) { // 채워야 할 부분
        printf("%d ", even[i]);
    }

    // print odd array
    printf("\n");
    printf("odd = ");
    for (i = 0; i < k; i++) {
        printf("%d ", odd[i]);
    }
    printf("\n");
    return 0;
}