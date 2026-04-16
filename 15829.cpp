#include <iostream>
#include <string>
using namespace std;

const long long MOD = 1234567891;
const long long R = 31;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int L;
    string s;
    cin >> L >> s;

    long long hashValue = 0;
    long long rPower = 1;  // r^i 저장용

    for (int i = 0; i < L; i++) {
        int value = s[i] - 'a' + 1;
        hashValue = (hashValue + value * rPower) % MOD;
        rPower = (rPower * R) % MOD;  // r^i 업데이트
    }

    cout << hashValue << "\n";
    return 0;
}
