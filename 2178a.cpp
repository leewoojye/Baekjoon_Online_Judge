#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int dx[4] = {0, -1, 1, 0};
int dy[4] = {-1, 0, 0, 1};

int main() {
    fastio;
    int N, M;
    cin >> N >> M;

    vector<vector<int>> arr(N, vector<int>(M, 0));
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> distance(N, vector<int>(M, 1));

    for(int i = 0; i < N; ++i) {
        string line;
        cin >> line;
        for(int k = 0; k < M; ++k) {
            arr[i][k] = line[k] - '0';
        }
    }

    int count = 1;
    int result = INT16_MAX;
    queue<pair<int, int>> q;
    q.push({0, 0});
    visited[0][0] = true;

    while(!q.empty()) {
        pair<int, int> front = q.front();
        int frontx = front.first;
        int fronty = front.second;
        if(frontx == N-1 && fronty == M-1) { break; }
        q.pop();
        bool flag=false;
        for(int i = 0; i < 4; ++i) {
            int nx = frontx + dx[i];
            int ny = fronty + dy[i];
            if(nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if(arr[nx][ny] == 0) continue;
            if(visited[nx][ny]) continue;
            q.push({nx, ny});
            visited[nx][ny] = true;
            flag=true;
        }
        if(flag) { count++; result=min(result,count); }
    }
    cout << result;
    return 0;
}
