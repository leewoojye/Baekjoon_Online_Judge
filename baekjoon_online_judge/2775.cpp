#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    int dp[15][15] = {0};

    for (int i = 1; i <= 14; ++i) {
        dp[0][i] = i;
    }

    for (int k = 1; k <= 14; ++k) {
        for (int n = 1; n <= 14; ++n) {
            dp[k][n] = dp[k][n-1] + dp[k-1][n];
        }
    }

    while (T--) {
        int k, n;
        cin >> k >> n;
        cout << dp[k][n] << '\n';
    }
    return 0;
}