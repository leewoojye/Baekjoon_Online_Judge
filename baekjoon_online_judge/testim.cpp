#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20, c = 30, d = 40;

    cout << "수정 이전: a=" << a << ", b=" << b << ", c=" << c << ", d=" << d << endl;

    int temp = a; 
    a = b;
    b = c;
    c = d;
    d = temp; 

    cout << "수정 이후: a=" << a << ", b=" << b << ", c=" << c << ", d=" << d << endl;

    return 0;
}