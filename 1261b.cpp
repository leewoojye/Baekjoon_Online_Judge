#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>
using namespace std;

struct state {
    int x, y, broken;
    state(int xP, int yP, int bP) : x(xP), y(yP), broken(bP) {}
    bool operator>(const state& other) const { 
        return broken > other.broken; // 다익스트라는 broken이 작은 순으로 정렬해야 함
    }
};

int N, M;
vector<vector<int>> maze;
vector<vector<int>> stateMap;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int bfs() {
    priority_queue<state, vector<state>, greater<state>> pq;
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    pq.push(state(0, 0, 0));
    stateMap[0][0] = 0;
    
    while (!pq.empty()) {
        state front = pq.top(); pq.pop();
        int x = front.x, y = front.y, broken = front.broken;

        // broken이 작은 state부터 탐색하므로 가장 먼저 종착지에 도착한 탐색이 최적해임.
        // 다익스트라는 처음 찾은 해가 최적해이기에 전역변수 best로 가지치기할 필요도 없음.
        if (x == N - 1 && y == M - 1) return broken; // 목표 지점 도착

        // broken이 적은 state부터 우선순위 큐에서 꺼내져 visit하게 되는데, 이미 한번이라도 방문한 좌표는 다음에 방문될 때보다 항상
        // 더 적은 broken으로 방문하게 된다. 따라서 각 상태 state마다 visited[]를 갖을 필요 없고, 전역으로 visited[] 배열을 하나 갖으면 된다.
        if (visited[x][y]) continue; // 이미 방문한 경우 스킵
        visited[x][y] = true;

        for (int i = 0; i < 4; ++i) {
            int nextx = x + dx[i];
            int nexty = y + dy[i];

            if (nextx < 0 || nextx >= N || nexty < 0 || nexty >= M) continue; // 범위 초과 방지

            // 0,1로만 이루어진 데이터 다루기 1.
            int newBroken = broken + maze[nextx][nexty];

            // newBroken은 항상 stateMap[] 원소보다 작으므로(최초 방문 좌표이기 때문) 패스, stateMap도 불필요
            // if (newBroken < stateMap[nextx][nexty]) {
            //     stateMap[nextx][nexty] = newBroken;
            //     pq.push(state(nextx, nexty, newBroken));
            // }
            pq.push(state(nextx, nexty, newBroken));
        }
    }
    return -1; // 도달할 수 없는 경우
}

int main() {
    cin >> M >> N;
    maze.resize(N, vector<int>(M));
    stateMap.resize(N, vector<int>(M, 987654321));
    // 0-based 인덱싱
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < M; ++j) {
            // 0,1로만 이루어진 데이터 다루기 2.
            maze[i][j] = s[j] - '0'; // '0' → 0, '1' → 1 변환
        }
    }
    auto start = chrono::high_resolution_clock::now();
    cout << bfs() << endl;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    cout << "실행 시간: " << elapsed.count() << " ms" << endl;
    return 0;
}
