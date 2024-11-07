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
            if(isEulerTrail(i, count++)) return true;
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
    for(int i=1;i<=V;++i) {
        int edges=0;
        for(int j=1;j<=V;++j) {
            edges+=matrix[i][j];
        }
        // 오일러 트레일인지 서킷인지 구분필요+
        // euler trail인 경우 - 시작점과 끝점이 다름
        if(edges%2 != 0) {
            string s;
            isEulerTrail(i, 0) ? s="YES" : s="NO";
            cout << s;
            return 0;
        } 
        // euler circuit인 경우 - 시작점과 끝점이 동일
        else {
            
        }
    }
    cout << "NO";
    return 0;
}