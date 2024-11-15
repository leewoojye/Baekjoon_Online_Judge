#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

// u번째 원소로 (w,v)를 저장
vector<vector<pair<unsigned char,int>>> edges;
vector<int> minDistance;

void searchDijkstra(unsigned short start) {
    priority_queue<pair<int, unsigned short>, vector<pair<int, unsigned short>>, greater<>> pq;
    pq.push({0,start});
    while(!pq.empty()) {
        pair<int,unsigned short> top=pq.top();
        int distance=top.first;
        minDistance[top.second]==-1 ? minDistance[top.second]=top.first : minDistance[top.second]=min(top.first,minDistance[top.second]);

        for(int i=0;i<edges[top.second].size();++i) {
            pq.push({top.first+static_cast<int>(edges[top.second][i].first), edges[top.second][i].second});
        }
        pq.pop();
    }
    return;
}

int main()
{
    fastio;
    unsigned short V,S;
    int E;
    unsigned short u,v;
    unsigned char w;
    cin >> V >> E;
    cin >> S;
    edges.resize(V+1);
    minDistance.resize(V+1, -1);
    
    int input;
    for(int i=0;i<E;++i) {
        cin >> u >> v >> input;
        w=static_cast<unsigned char>(input);
        edges[u].push_back({w,v});
    }
    searchDijkstra(S);
    for(unsigned short i = 1; i <= V; ++i) {
    if (i == S) {
        cout << 0 << '\n'; 
        continue;
    }
    if (minDistance[i] == -1) {
        cout << "INF" << '\n';
        continue;
    }
    cout << minDistance[i] << '\n';
    }
    return 0;
}