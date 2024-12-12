#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
    fastio;
    int E;
    cin >> E;
    
    // 용량을 나타내는 배열 초기화, INT_MAX 대신 0으로 초기화
    vector<vector<int>> flow(26, vector<int>(26, 0));
    
    char c1, c2;
    int f;
    for (int i = 0; i < E; ++i) {
        cin >> c1 >> c2 >> f;
        flow[c1 - 'A'][c2 - 'A'] += f;  // 양방향이므로 양쪽에 용량을 더함
    }
    
    int ret = 0;
    while (true) {
        vector<bool> visited(26, false);
        vector<int> parent(26, -1);
        parent[0] = 0;  // 시작 노드는 자기 자신을 부모로 설정
        visited[0] = true;
        queue<int> q;
        q.push(0);
        int amount = INT_MAX;

        // BFS로 경로를 찾음
        while (!q.empty() && parent[25] == -1) {
            int front = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                // 방문하지 않았고, 유량이 0보다 크면 경로로 선택
                if (!visited[i] && flow[front][i] > 0) {
                    visited[i] = true;
                    parent[i] = front;
                    amount = min(amount, flow[front][i]);
                    q.push(i);
                }
            }
        }

        // 25번 노드(목표 노드)에 도달하지 못하면 종료
        if (parent[25] == -1) break;

        // 역추적해서 경로를 따라 유량을 보냄
        for (int p = 25; p != 0; p = parent[p]) {
            flow[p][parent[p]] -= amount;  // 역방향 유량 감소
            flow[parent[p]][p] += amount;  // 순방향 유량 증가
        }
        
        ret += amount;  // 총 유량에 추가
    }

    cout << ret << '\n';
    return 0;
}
