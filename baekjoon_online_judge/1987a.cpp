#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<char>> matrix;
int R, C;
int maxCount = 0;
vector<int> dx = {0, 0, -1, 1}; // 상하좌우 이동
vector<int> dy = {1, -1, 0, 0}; 

// code point!
// 각 재귀호출마다 다른 배열을 전달하려할때 데이터복사가 아닌 &참조를 전달해도 구현가능함. -> visited[nextChar - 'A'] = false; // 방문 해제 부분
// 데이터를 좌표로 나타낼때 이동범위를 벡터의 원소값 -1 0 1로 표현 가능, dx/dy를 변수화한다는 발상!
// 범위벗어나는 상황 분기처리를 OR를 통해 간단하게 나타낼 수 있음. -> if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
// 방문여부를 나타내는 배열명은 그냥 visited으로 통일하자...
// dfs/bfs 탐색시 전역변수 maxCount와 지역변수 count를 통해 탐색과 동시에 경로의 길이를 갱신해줄 수 있음.
// 트리를 직접 구현하여 메모리에 따로 할당까지하면 차지하는 메모리가 많아진다...

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
