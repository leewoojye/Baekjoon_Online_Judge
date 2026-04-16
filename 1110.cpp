#include <iostream>
using namespace std;

int main() {
    int N, temp, count = 0;
    cin >> N;
    int num = N;
    do {
        int a = num / 10;
        int b = num % 10;
        int sum = a + b;
        num = b * 10 + (sum % 10);
        count++;
    } while (num != N);
    cout << count << endl;
    return 0;
}