#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> files(N + 1);  // 파일 크기
        vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
        vector<vector<int>> sum(N + 1, vector<int>(N + 1, 0));
        // 파일 크기 입력
        for (int i = 1; i <= N; i++) {
            cin >> files[i];
        }
        // 누적합 계산
        for (int i = 1; i <= N; i++) {
            sum[i][i] = files[i];
            for (int j = i + 1; j <= N; j++) {
                sum[i][j] = sum[i][j - 1] + files[j];
            }
        }
        // DP 테이블을 채우기
        for (int length = 2; length <= N; length++) {
            for (int i = 1; i <= N - length + 1; i++) {
                int j = i + length - 1;
                dp[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[i][j]);
                }
            }
        }
        // 최소 비용 출력
        cout << dp[1][N] << endl;
    }
    return 0;
}
