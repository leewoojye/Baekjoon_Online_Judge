#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int V,E;
vector<vector<int>> matrix;
bool isEulerTrail(int here, int count) {
    for(int i=1;i<=V;++i) {
        if(matrix[here][i]>0) {
            matrix[here][i]--;
            matrix[i][here]--;
            if(isEulerTrail(i, count+1)) return true;
            matrix[here][i]++;
            matrix[i][here]++;
        }
    }
    if(count==E) return true;
    return false;
}

int main()
{
    fastio;
    int e1,e2;
    cin >> V >> E;
    matrix.resize(V+1, vector<int>(V+1, 0));
    for(int i=0;i<E;++i) {
        cin >> e1 >> e2;
        matrix[e1][e2]++;
        matrix[e2][e1]++;
    }
    int flag=false;
    for(int i=1;i<=V;++i) {
        // 차수가 홀수인 정점이 하나라도 있으면 홀수점을 시작점으로 잡는다.
        int edges=0;
        for(int j=1;j<=V;++j) {
            edges+=matrix[i][j];
        }
        if(edges%2!=0) flag=true;
        if(edges%2!=0 && isEulerTrail(i, 0)) {
            cout << "YES";
            return 0;
        }
    }
    for(int i=0;i<=V;++i) {
        if(!flag && isEulerTrail(i, 0)) {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}