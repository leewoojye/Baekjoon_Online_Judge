#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    int p = 10;
    while (N >= p) {
        if (N % p >= p / 2) {
            N += p - (N % p);
        } else {
            N -= (N % p);
        }
        p *= 10;
    }
    cout << N << endl;
    return 0;
}