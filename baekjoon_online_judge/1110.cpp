#include <iostream>
using namespace std;

int main() {
    int N, temp, count = 0;
    cin >> N;
    int num = N;
    do {
        // 각 자리수 더하기
        int a = num / 10;
        int b = num % 10;
        int sum = a + b;
        // 새로운 수 만들기
        num = b * 10 + (sum % 10);
        count++;
    } while (num != N);
    cout << count << endl;
    return 0;
}