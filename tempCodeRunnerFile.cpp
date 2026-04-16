#include <iostream>

class Count {
private:
    int num;

public:
    Count(int n = 0) {
        num = n;
        std::cout << "기본 생성자 호출 (num = " << num << ")" << std::endl;
    }

    Count(int n1, int n2) {
        num = (n1 > n2) ? n1 : n2; 
        std::cout << "오버로딩된 생성자 호출 (num = " << num << ")" << std::endl;
    }

    void Print() {
        std::cout << "현재 num 값: " << num << std::endl;
    }
};

int main() {
    Count c1;
    c1.Print();

    Count c2(10);
    c2.Print();

    Count c3(20, 30); 
    c3.Print();

    Count c4(100, 50); 
    c4.Print();

    return 0;
}