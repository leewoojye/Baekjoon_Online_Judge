#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// 	ios_base::sync_with_stdio(false); // c와 c++의 표준 입출력 스트림을 동기화를 하지 않겠다는 의미

int main() {
    ios_base::sync_with_stdio(false);
    int num1, num2, num3;
    cin >> num1 >> num2;

    vector<int> numbers;
    for (int i = 0; i < num1; ++i) {
        int num;
        cin >> num; // 두 번째 줄에서 num1 만큼 입력 받기
        numbers.push_back(num);
    }
    sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b; // a가 b보다 크면 true를 반환하여 내림차순 정렬
    });

    for (int i = 0; i < numbers.size(); i++) {
        for (int n = 1; n < numbers.size()-1; n++) {
            for (int m = 2; m < numbers.size()-2; m++) {
                if (numbers[i] + numbers[n] + numbers[m] < num2) {
                    num3 = numbers[i] + numbers[n] + numbers[m];
                    break;
                }
            }
        }
    }

    cout << num3 << '\n';

    return 0;
}

/* void picked(vector<int>& picked, int toPick, int n) { // n은 넘지 말아야 할 한계치인 num2
    if(toPick == 0 && accumulate(picked.begin(), picked.end(), 0) < n) { return; }
    int largest = picked.empty() ? 0 : picked.back();
    for (int next = largest; next >= 0; n--) {
        picked.pus
    }
} */