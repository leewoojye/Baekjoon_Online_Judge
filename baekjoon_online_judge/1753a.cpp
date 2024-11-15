#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <climits>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

// u번째 원소로 (w,v)를 저장
vector<vector<pair<unsigned char, unsigned short>>> edges;
vector<int> minDistance;

void searchDijkstra(unsigned short start) {
    priority_queue<pair<int, unsigned short>, vector<pair<int, unsigned short>>, greater<>> pq;
    pq.push({0, start});
    minDistance[start] = 0;  // 시작점의 거리 0으로 설정

    while (!pq.empty()) {
        pair<int, unsigned short> top = pq.top();
        pq.pop();
        
        int distance = top.first;
        unsigned short currentNode = top.second;

        // 이미 더 작은 거리로 방문한 노드라면 건너뛰기
        if (distance > minDistance[currentNode]) continue;

        // 현재 정점에서 연결된 모든 간선 처리
        for (auto& edge : edges[currentNode]) {
            unsigned char weight = edge.first;
            unsigned short nextNode = edge.second;

            int newDistance = distance + static_cast<int>(weight);  // 새로운 거리 계산

            // 더 작은 거리로 갱신 (min() 사용)
            if (minDistance[nextNode] == -1 || newDistance < minDistance[nextNode]) {
                minDistance[nextNode] = newDistance;
                pq.push({newDistance, nextNode});
            }
        }
    }
}

int main() {
    fastio;
    unsigned short V, S;
    int E;
    unsigned short u, v;
    unsigned char w;
    cin >> V >> E >> S;
    
    // 인접 리스트 크기 최적화: V+1 크기만큼 할당
    edges.resize(V + 1);
    minDistance.resize(V + 1, -1);  // 거리 초기화 (-1은 방문하지 않음)

    // 간선 입력 받기
    int input;
    for (int i = 0; i < E; ++i) {
        cin >> u >> v >> input;
        w=static_cast<unsigned char>(input);
        edges[u].push_back({w, v});
    }

    searchDijkstra(S);  // 다익스트라 알고리즘 실행

    // 출력
    for (unsigned short i = 1; i <= V; ++i) {
        if (minDistance[i] == -1) {
            cout << "INF\n";  // 도달할 수 없는 경우
        } else {
            cout << minDistance[i] << '\n';  // 최단 거리 출력
        }
    }

    return 0;
}
