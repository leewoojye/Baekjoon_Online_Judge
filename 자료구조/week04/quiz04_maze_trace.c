/*
Quiz
1. 미로탐색 코드를 통해 아래 미로를 돌려보아라.
2. 다음과 같은 미로 탐색을 하였을 경우 알고리즘의 각 단계에서 스택의 모습을 그려라.

111111
000011
110111
110111
100000
111111

예시 답안
- 예시 시작점: (1, 0)
- 예시 출구점: (4, 5)
- 한 가지 도달 경로 예시:
  (1,0) -> (1,1) -> (1,2) -> (2,2) -> (3,2) -> (4,2) -> (4,3) -> (4,4) -> (4,5)
- 아래 코드는 스택 기반 DFS로 진행 과정과 스택 상태를 출력한다.
*/

#include <stdio.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

typedef struct {
    int r;
    int c;
} Position;

typedef struct {
    Position data[MAX_STACK_SIZE];
    int top;
} StackType;

char maze[MAZE_SIZE][MAZE_SIZE + 1] = {
    "111111",
    "000011",
    "110111",
    "110111",
    "100000",
    "111111",
};

void init_stack(StackType *s)
{
    s->top = -1;
}

int is_empty(StackType *s)
{
    return s->top == -1;
}

void push(StackType *s, Position item)
{
    s->data[++(s->top)] = item;
}

Position pop(StackType *s)
{
    return s->data[(s->top)--];
}

int is_open_cell(int r, int c)
{
    return r >= 0 && r < MAZE_SIZE && c >= 0 && c < MAZE_SIZE && maze[r][c] == '0';
}

void print_stack(StackType *s)
{
    printf("stack: ");
    for (int i = 0; i <= s->top; i++) {
        printf("(%d,%d) ", s->data[i].r, s->data[i].c);
    }
    if (s->top == -1) {
        printf("(empty)");
    }
    printf("\n");
}

int main(void)
{
    StackType s;
    Position start = {1, 0};
    Position exit = {4, 5};
    Position current;

    init_stack(&s);
    push(&s, start);

    while (!is_empty(&s)) {
        current = pop(&s);
        printf("visit: (%d,%d)\n", current.r, current.c);

        if (current.r == exit.r && current.c == exit.c) {
            printf("exit found at (%d,%d)\n", exit.r, exit.c);
            return 0;
        }

        if (maze[current.r][current.c] != '0') {
            continue;
        }

        maze[current.r][current.c] = '.';

        if (is_open_cell(current.r - 1, current.c)) {
            push(&s, (Position){current.r - 1, current.c});
        }
        if (is_open_cell(current.r + 1, current.c)) {
            push(&s, (Position){current.r + 1, current.c});
        }
        if (is_open_cell(current.r, current.c - 1)) {
            push(&s, (Position){current.r, current.c - 1});
        }
        if (is_open_cell(current.r, current.c + 1)) {
            push(&s, (Position){current.r, current.c + 1});
        }

        print_stack(&s);
    }

    printf("no path found\n");
    return 0;
}
