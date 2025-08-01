#include <iostream>
using namespace std;

int main() {
    for (int i = 0; i < 3; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int sum = a + b + c + d;

        switch (sum) {
            case 0: cout << "D\n"; break; // 0 0 0 0
            case 1: cout << "C\n"; break; // 1 0 0 0
            case 2: cout << "B\n"; break; // 1 1 0 0
            case 3: cout << "A\n"; break; // 1 1 1 0
            case 4: cout << "E\n"; break; // 1 1 1 1
        }
    }
    return 0;
}