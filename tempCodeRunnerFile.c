#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int main()
{
    char s1[MAX_SIZE]; char* s2 = NULL; char* s3 = NULL;

    printf("Enter your name: ");
    gets(s1);

    s2 = (char*)malloc(strlen(s1) + 1);
    strcpy(s2, s1);

    s3 = s1 + 3;
    s1[10] = '\0';

    printf("s1=%s; s2=%s; s3=%s\n", s1, s2, s3);

    free(s2);

    return 0;
}