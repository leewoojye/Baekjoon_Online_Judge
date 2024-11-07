#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

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

    // 시간 측정 시작
    auto start = high_resolution_clock::now();
    
    int e1, e2;
    cin >> V >> E;
    matrix.resize(V + 1, vector<int>(V + 1, 0));
    
    // 간선 입력 처리
    for(int i = 0; i < E; ++i) {
        cin >> e1 >> e2;
        matrix[e1][e2]++;
        matrix[e2][e1]++;
    }

    for(int i = 1; i <= V; ++i) {
        if(isEulerTrail(i, 0)) {
            cout << "YES";
            // 시간 측정 종료
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);  // 밀리초 단위
            cout << "\nTime: " << duration.count() << " ms\n";
            return 0;
        }
    }

    cout << "NO";
    // 시간 측정 종료
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);  // 밀리초 단위
    cout << "\nTime: " << duration.count() << " ms\n";
    
    return 0;
}
