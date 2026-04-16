#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studentTag {
    char name[10];
    int age;
    double gpa;
} student;

int main(void)
{
    student *p;

    p = (student *)malloc(sizeof(student));
    if (p == NULL) {
        fprintf(stderr, "Not enough memory.\n");
        exit(1);
    }

    strcpy(p->name, "Park");
    p->age = 20;
    p->gpa = 4.2;

    printf("%s %d %.1f\n", p->name, p->age, p->gpa);

    free(p);
    return 0;
}
