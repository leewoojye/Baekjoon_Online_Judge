#include <iostream>
#include <string>

int main() {
    int A, B, C;
    std::cin >> A >> B >> C;

    int product = A * B * C;
    int count[10] = {0};

    std::string result = std::to_string(product);
    for (char digit : result) {
        count[digit - '0']++;
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << count[i] << std::endl;
    }

    return 0;
}