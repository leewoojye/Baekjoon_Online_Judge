#include <iostream>
#include <vector>
#include <numeric>

int main() {
    // 입출력 속도 향상
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int M;
    std::cin >> M;

    // 공의 현재 위치를 나타내는 변수.
    // 초기 위치는 1번 컵입니다.
    int ball_location = 1;

    for (int i = 0; i < M; ++i) {
        int X, Y;
        std::cin >> X >> Y;

        // 공이 현재 위치한 컵이 X 또는 Y라면, 공의 위치를 바꿔줍니다.
        if (ball_location == X) {
            ball_location = Y;
        } else if (ball_location == Y) {
            ball_location = X;
        }
    }

    std::cout << ball_location << std::endl;

    return 0;
}