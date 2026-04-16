#include <iostream>
#include <string>
using namespace std;

int main() {
    string N;
    cin >> N;
    int len = N.size();

    bool isYujinsu = false;
    for (int i = 1; i < len; ++i) {
        int leftMul = 1;
        int rightMul = 1;
        for (int j = 0; j < i; ++j)
            leftMul *= N[j] - '0';
        for (int j = i; j < len; ++j)
            rightMul *= N[j] - '0';
        if (leftMul == rightMul) {
            isYujinsu = true;
            break;
        }
    }
    cout << (isYujinsu ? "YES" : "NO") << endl;
    return 0;
}