#include <iostream>
using namespace std;

int dp[31][31];

int comb(int n, int r) {
    if(dp[n][r] != 0) return dp[n][r];
    if(r == 0 || n == r) return dp[n][r] = 1;
    return dp[n][r] = comb(n-1, r-1) + comb(n-1, r);
}

int main() {
    int T, N, M;
    cin >> T;
    while(T--) {
        cin >> N >> M;
        cout << comb(M, N) << '\n';
    }
}