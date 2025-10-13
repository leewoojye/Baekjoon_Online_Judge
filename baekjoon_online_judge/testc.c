#include <stdio.h>
#define SIZE 5

int data[SIZE] = {0, 10, 20, 30, 40};
// 아래 4줄 완성
int next[SIZE] = {-1, 3, 1, 0, 2};
int prev[SIZE] = {3, 2, 4, 1, -1};
int head = 4;
int last = 0;

void PrintList()
{
    int i;
    printf("(head = %d) => ", head);
    for (i = head; i != -1; i = next[i])
    {
        printf("%d (next = %d) => ", data[i], next[i]);
    }
    printf("(null)\n(last = %d) => ", last);
    for (i = last; i != -1; i = prev[i]) {
        printf("%d (prev = %d) => ", data[i], prev[i]);
    }
    printf("(null)\n");
}

int main()
{
    PrintList();
    return 0;
}