#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> matrix;
vector<vector<int>> dp; // DP 배열
int N, fullvisited;

// visited 목록의 도시를 거쳐 here까지 왔을 때 최소 비용 반환
int searchTSP(int visited, int here) {
    if (visited == fullvisited) {
        return matrix[here][0] ? matrix[here][0] : INT_MAX; // 시작점으로 돌아갈 수 있는지 확인
    }

    if (dp[visited][here] != -1) return dp[visited][here]; // 이미 계산한 값 반환

    int ret = INT_MAX;
    for (int next = 0; next < N; ++next) {
        if (visited & (1 << next)) continue; // 이미 방문한 도시 건너뜀
        if (matrix[here][next] == 0) continue; // 연결되지 않은 도시 건너뜀

        int cost = searchTSP(visited | (1 << next), next);
        if (cost != INT_MAX) ret = min(ret, cost + matrix[here][next]);
    }

    return dp[visited][here] = ret; // 결과 저장 및 반환
}

int main() {
    fastio;
    cin >> N;
    matrix.resize(N, vector<int>(N));
    dp.resize(1 << N, vector<int>(N, -1)); // DP 배열 초기화
    fullvisited = (1 << N) - 1; // 모든 도시를 방문한 상태

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> matrix[i][j];
        }
    }

    int result = searchTSP(1, 0); // 시작점에서 출발
    cout << (result == INT_MAX ? -1 : result) << '\n'; // 결과 출력
    return 0;
}
