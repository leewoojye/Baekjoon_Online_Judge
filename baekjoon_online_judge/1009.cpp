#include <iostream>
using namespace std;

// a^b % 10을 빠르게 구하는 함수
int last_digit(int a, int b) {
    int result = 1;
    a = a % 10;
    for (int i = 0; i < b; ++i) {
        result = (result * a) % 10;
    }
    return result == 0 ? 10 : result;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int a, b;
        cin >> a >> b;

        int res = 1;
        a = a % 10;
        if (a == 0) {
            cout << 10 << endl;
            continue;
        }
        
        int cycle[10], cycle_len = 0;
        int temp = a;
        do {
            cycle[cycle_len++] = temp;
            temp = (temp * a) % 10;
        } while (temp != a);
        int idx = (b - 1) % cycle_len;
        cout << cycle[idx] << endl;
    }
    return 0;
}