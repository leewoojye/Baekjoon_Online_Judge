#include <iostream>

int main() {
    const int N = 5;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            // 첫 행, 마지막 행, 첫 열, 마지막 열인 경우에만 별 출력
            if (i == 1 || i == N || j == 1 || j == N) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}