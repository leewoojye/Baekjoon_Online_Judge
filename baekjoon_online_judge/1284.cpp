#include <iostream>
#include <string>

int main() {
    std::string s;
    while (std::cin >> s && s != "0") {
        int totalWidth = 0;
        
        // 왼쪽 끝 여백 (1cm) + 오른쪽 끝 여백 (1cm)
        totalWidth += 2;
        
        // 각 숫자 사이의 여백 (자릿수-1 만큼)
        totalWidth += s.length() - 1;
        
        for (char c : s) {
            if (c == '1') {
                totalWidth += 2;
            } else if (c == '0') {
                totalWidth += 4;
            } else {
                totalWidth += 3;
            }
        }
        std::cout << totalWidth << std::endl;
    }
    return 0;
}