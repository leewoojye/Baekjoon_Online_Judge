#include <stdio.h>

int fib_iter(int n)
{
    int pp;
    int p;
    int result;

    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    pp = 0;
    p = 1;
    result = 0;
    for (int i = 2; i <= n; i++) {
        result = p + pp;
        pp = p;
        p = result;
    }
    return result;
}

int fib_iter2(int n)
{
    int pp;
    int p;
    int result;

    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    pp = 0;
    p = 1;
    result = 0;
    for (int i = 2; i <= n; i++) {
        result = p + pp;
        pp = p;
        p = result;
    }
    return result;
}

int main() {
    int result = fib_iter(5);
    printf("%d",result);
    return 0;
}