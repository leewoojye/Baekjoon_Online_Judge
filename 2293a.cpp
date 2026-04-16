#include <iostream>
#include <vector>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int main() {
    fastio;
    int n, k;
    cin >> n >> k;
    vector<int> coins(n);
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }
    
    // DP 테이블 초기화
    vector<int> dp(k + 1, 0);
    dp[0] = 1; // 금액 0을 만드는 방법은 1가지

    // 동전 순회
    for (int i = 0; i < n; ++i) {
        for (int j = coins[i]; j <= k; ++j) {
            dp[j] += dp[j - coins[i]];
        }
    }

    // 결과 출력
    cout << dp[k] << "\n";
    return 0;
}