#include <stdio.h>
#include <string.h>

typedef struct studentTag {
    char name[10];
    int age;
    double gpa;
} student;

int main(void)
{
    struct studentTag s1;
    student s;
    student a = {"kim", 20, 4.3};
    student b = {"park", 21, 4.2};

    strcpy(s1.name, "kim");
    s1.age = 20;
    s1.gpa = 4.3;

    s = a;

    printf("%s %d %.1f\n", s1.name, s1.age, s1.gpa);
    printf("%s %d %.1f\n", s.name, s.age, s.gpa);
    printf("%s %d %.1f\n", b.name, b.age, b.gpa);
    return 0;
}
