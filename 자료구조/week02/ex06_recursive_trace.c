#include <stdio.h>

/*
 * Introductory recursion trace example from the lecture.
 * The slide emphasizes that every recursive call must converge to a base condition.
 * This version uses n == 0 as the terminating condition so the call chain ends.
 */
void recursive(int n)
{
    printf("recursive(%d)\n", n);
    if (n == 0) {
        return;
    }
    recursive(n - 1);
}

int main(void)
{
    recursive(3);
    return 0;
}
