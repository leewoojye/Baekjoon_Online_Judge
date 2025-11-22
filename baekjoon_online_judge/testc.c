#include <stdio.h>

typedef struct Student {
    void (*Print) (char *s);
} Student;

void PrintFreshman(char *name) { printf("%s is a freshman\n", name); }
void PrintSophomore(char *name) { printf("%s is a sophomore\n", name); }

int main()
{
    Student s1 = {PrintFreshman};
    Student s2 = {PrintSophomore};
    
    s1.Print("Kim");
    s2.Print("Lee");
    
    return 0;
}