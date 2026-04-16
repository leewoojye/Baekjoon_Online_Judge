#include <iostream>

using namespace std;

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

int main() {
    int N, K;
    cin >> N >> K;
    // 이항 계수 공식: N! / (K! * (N-K)!)
    int answer = factorial(N) / (factorial(K) * factorial(N - K));
    cout << answer << endl;
    return 0;
}