#include <stdio.h>

void hanoi_tower(int n, char from, char tmp, char to)
{
    if (n == 1) {
        printf("Move disk 1 from %c to %c.\n", from, to);
    } else {
        hanoi_tower(n - 1, from, to, tmp);
        printf("Move disk %d from %c to %c.\n", n, from, to);
        hanoi_tower(n - 1, tmp, from, to);
    }
}

int main(void)
{
    hanoi_tower(4, 'A', 'B', 'C');
    return 0;
}
