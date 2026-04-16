#include <iostream>
#include <string>

using namespace std;

int main() {
    string K_str;
    int L;
    cin >> K_str >> L;
    long long mod = 0;

    for (int i = 2; i < L; ++i) {
        mod = 0;
        for (int j = 0; j < K_str.size(); ++j) {
            mod = (mod * 10 + (K_str[j] - '0')) % i;
        }
        if (mod == 0) {
            cout << "BAD " << i << endl;
            return 0;
        }
    }
    cout << "GOOD" << endl;
    return 0;
}