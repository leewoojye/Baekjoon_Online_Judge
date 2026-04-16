#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    clock_t start, end;
    start = clock();

    int num1, num2;
    cin >> num1 >> num2;

    vector<int> numbers(num1); // num1 크기의 벡터 선언

    for (int i = 0; i < num1; ++i) {
        cin >> numbers[i]; // num1 개의 숫자를 입력받아 벡터에 저장
    }

    sort(numbers.begin(), numbers.end(), greater<int>()); // 내림차순 정렬

    int num3 = 0; // num3 변수 초기화

    // 세 개의 숫자를 선택하여 조건 만족하는지 확인
    for (int i = 0; i < numbers.size() - 2; ++i) {
        for (int n = i + 1; n < numbers.size() - 1; ++n) {
            for (int m = n + 1; m < numbers.size(); ++m) {
                int sum = numbers[i] + numbers[n] + numbers[m];
                if (sum <= num2) {
                    num3 = sum;
                    break;
                }
            }
            if (num3 != 0) break;
        }
        if (num3 != 0) break;
    }

    cout << num3 << '\n';

    end = clock();
    double result = (double)(end - start);
    cout << result;

    return 0;
}
