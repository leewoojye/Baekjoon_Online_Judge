#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int V, E;
vector<vector<int>> matrix;

bool isEulerTrail(int here, int count) {
    for(int i = 1; i <= V; ++i) {
        if(matrix[here][i] > 0) {
            matrix[here][i]--;
            matrix[i][here]--;
            if(isEulerTrail(i, count + 1)) return true;
            matrix[here][i]++;
            matrix[i][here]++;
        }
    }
    if(count == E) return true;
    return false;
}

int main() {
    fastio;
    int e1, e2;
    cin >> V >> E;
    matrix.resize(V + 1, vector<int>(V + 1, 0));
    vector<int> degree(V + 1, 0);

    // 간선 입력 받으면서 차수 계산
    for(int i = 0; i < E; ++i) {
        cin >> e1 >> e2;
        matrix[e1][e2]++;
        matrix[e2][e1]++;
        degree[e1]++;
        degree[e2]++;
    }

    // 홀수 차수인 정점 찾기
    int oddCount = 0;
    int startVertex = -1;
    for(int i = 1; i <= V; ++i) {
        if(degree[i] % 2 != 0) {
            oddCount++;
            startVertex = i;  // 홀수 차수인 정점 하나를 시작점으로 잡음
        }
    }

    // Eulerian Trail 조건: 홀수 차수 정점이 0개 또는 2개여야만 가능
    if(oddCount != 0 && oddCount != 2) {
        cout << "NO";
        return 0;
    }

    // DFS 호출
    if(isEulerTrail(startVertex != -1 ? startVertex : 1, 0)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}