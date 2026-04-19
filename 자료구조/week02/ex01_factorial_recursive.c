#include <stdio.h>
#include <stdlib.h>

// int factorial(int n)
// {
//     if (n <= 1) {
//         return 1;
//     }
//     return n * factorial(n - 1);
// }

int power(double x, int n) {
    if(n==0) return 1;
    if (n%2==0) return power(x*x,n/2);
    return x*power(x*x,(n-1)/2);
}

int main() {
    int result = power(2,3);
    printf("%d\n",result);
    return 0;
}