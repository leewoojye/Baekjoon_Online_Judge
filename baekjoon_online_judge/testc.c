#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    char s1[] = "LEE WOOJYE"; 
    char s2[MAX];
    int len = strlen(s1);
    int i, j;

    for (i = len - 1, j = 0; i >= 0; i--, j++) {
        s2[j] = s1[i];
    }
    s2[len] = '\0'; 

    printf("Before: %s\n", s1);
    printf("After: %s\n", s2);

    return 0;
}