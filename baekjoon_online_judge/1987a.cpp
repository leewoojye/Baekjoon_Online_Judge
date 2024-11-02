#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<char>> matrix;
int R, C;
int maxCount = 0;
vector<int> dx = {0, 0, -1, 1}; // 상하좌우 이동
vector<int> dy = {1, -1, 0, 0}; 

void dfs(int x, int y, int count, vector<bool>& visited) {
    maxCount = max(maxCount, count);
    
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        // 범위 체크
        if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
        char nextChar = matrix[nx][ny];

        // 방문 여부 체크
        if (!visited[nextChar - 'A']) {
            visited[nextChar - 'A'] = true; // 방문 처리
            dfs(nx, ny, count + 1, visited);
            visited[nextChar - 'A'] = false; // 방문 해제
        }
    }
}

int main() {
    fastio;
    cin >> R >> C;
    matrix.resize(R, vector<char>(C));
    
    for (int i = 0; i < R; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < C; ++j) {
            matrix[i][j] = s[j];
        }
    }

    vector<bool> visited(26, false); // 알파벳 방문 체크
    visited[matrix[0][0] - 'A'] = true; // 시작 위치 방문 처리
    dfs(0, 0, 1, visited);

    cout << maxCount << endl;
    return 0;
}
