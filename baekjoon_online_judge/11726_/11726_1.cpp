#include<iostream>
using namespace std;

int dp[1000] = { 0, };

long long tile(int n) {
    dp[1] = 1;
    dp[2] = 2;
    if (dp[n] != 0)return dp[n];
    else return dp[n] = tile(n - 1) + tile(n - 2);
}

int main() {
    int number;
    int result;
    cin >> number;

    result = tile(number) % 10007;
    cout << result;
    return 0;
}

// https://www.acmicpc.net/board/view/139004