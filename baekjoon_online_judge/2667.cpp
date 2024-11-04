#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

vector<vector<int>> matrix;
vector<vector<bool>> visited;
vector<int> result;
int indexx=0;
int dx[4]={0,1,-1,0};
int dy[4]={1,0,0,-1};

void searchDFS(int x, int y) {
    for(int i=0;i<4;++i) {
        int newx=x+dx[i];
        int newy=y+dy[i];
        if(newx<0 || newx>matrix.size()-1 || newy<0 || newy>matrix.size()-1 || visited[newx][newy]) continue;
        if(matrix[newx][newy]==1) {
            result[indexx]++;
            searchDFS(newx, newy);
        }
    }
    return;
}

int main()
{
    fastio;
    int N;
    string s;
    cin >> N;
    matrix.resize(N, vector<int>(N));
    visited.resize(N, vector<bool>(N));
    for(int i=0;i<N;++i) {
        cin >> s;
        for(int j=0;j<N;++j) {
            matrix[i].push_back((int)s[j]);
        }
    }
    for(int x=0;x<N;++x) {
        for(int y=0;y<N;++y) {
            if(matrix[x][y]==1 && !visited[x][y]) {
                searchDFS(x, y);
                result.push_back(0);
                indexx++;
            }
        }
    }
    sort(result.begin(), result.end());
    cout << result.size() << '\n';
    for(auto& o : result) {
        cout << o;
    }
    return 0;
}