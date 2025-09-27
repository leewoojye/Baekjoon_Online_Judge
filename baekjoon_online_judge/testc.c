#include <stdio.h>
#define MAX 1000 // max # of digits

int main()
{ // Calculate 12^30
    int base = 12, power = 30, result[MAX], mult, carry, i, k, flag = 0;

    // initialization: result = 1
    result[0] = 1;
    for (i = 1; i < MAX; i++) {
        result[i] = 0;
    }

    // calculate base^power
    for (i = 0; i < power; i++) {
        // result = result * base;
        carry = 0;
        for (k = 0; k < MAX; k++) {
            mult = result[k] * base + carry;
            result[k] = mult % 10; // 채워야 할 부분
            carry = mult / 10;
        }
    }

    // print base^power
    printf("%d^%d = ", base, power);
    for (i = MAX - 1; i >= 0; i--) {
        if (result[i] > 0) flag = 1;
        if (flag) printf("%d", result[i]);
    }
    printf("\n");
    return 0;
}