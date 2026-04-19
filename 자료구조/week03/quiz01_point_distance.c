/*
Quiz
1. 2차원 좌표 공간에서 하나의 점을 나타내는 구조체 Point를 정의하여 보라.
   typedef도 사용하여서 구조체 Point를 하나의 타입으로 정의한다.
2. 1에서 정의한 구조체 변수인 p1과 p2를 정의하여 보라.
3. p1과 p2를 각각 (1, 2)와 (9, 8)로 초기화 하라.
4. 점을 나타내는 두 개의 구조체 변수를 받아서 점 사이의 거리를 계산하는
   함수 get_distance(Point p1, Point p2)를 작성하여 보자.

예시 답안
- Point는 x, y 좌표를 가지는 구조체로 정의한다.
- p1 = (1, 2), p2 = (9, 8)
- 두 점 사이의 거리는 sqrt((x2-x1)^2 + (y2-y1)^2)
*/

#include <math.h>
#include <stdio.h>

typedef struct {
    double x;
    double y;
} Point;

double get_distance(Point p1, Point p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    return sqrt(dx * dx + dy * dy);
}

int main(void)
{
    Point p1 = {1.0, 2.0};
    Point p2 = {9.0, 8.0};

    printf("p1 = (%.0f, %.0f)\n", p1.x, p1.y); // 소수점 없이 실수 출력
    printf("p2 = (%.0f, %.0f)\n", p2.x, p2.y);
    printf("distance = %.2f\n", get_distance(p1, p2));
    return 0;
}
