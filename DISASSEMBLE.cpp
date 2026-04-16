#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <numeric>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int num1, num2;
    int num3;
    cin >> num1;
    vector<int> digit;

    for (int i = 1; i < num1; i++) {
        while (i > 0) {
            digit.push_back(i % 10); // 일의 자리 숫자 추출
            i /= 10; // 다음 자리로 이동
        }
        num2 = i + accumulate(digit.begin(), digit.end(), 0);

        if (num2 == num1) {
            num3 = i;
            break;
        }
    }
    if(num2 != num1) {
        cout << "error";
    }
    cout << num3;
    return 0;
}
