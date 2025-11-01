#include <stdio.h>

int Sum(int n) {
    if (n <= 1) { 
        return n;
    } else {
        return n + Sum(n - 1);
    }
}

int main() {
    int n = 5;
    int result = Sum(n);
    
    printf("sum = ");
    for (int i = n; i > 0; i--) {
        printf("%d", i);
        if (i > 1) {
            printf(" + ");
        }
    }
    printf(" = %d\n", result);
    
    return 0;
}