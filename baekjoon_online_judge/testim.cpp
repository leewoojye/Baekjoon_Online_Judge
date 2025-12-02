#include <iostream>
using namespace std;

class Count {
    int num;
public:
    void Reset() { num = 0; }
    void Print() { cout << num << endl; }
    void Increment() { num++; }
    void Double() { num *= 2; } // 추가된 함수
};

int main() {
    Count c;
    c.Reset();
    c.Increment(); // 1
    c.Increment(); // 2
    c.Double();    // 4
    c.Print();
    return 0;
}