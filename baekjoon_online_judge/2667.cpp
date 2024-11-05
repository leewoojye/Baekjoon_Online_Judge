#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

vector<vector<int>> matrix;
vector<vector<bool>> visited;
// 각 구역의 결과를 저장하는 벡터
vector<int> result;
// 구역번호를 저장하는 변수 indexx
int indexx=0;
int dx[4]={0,1,-1,0};
int dy[4]={1,0,0,-1};

void searchDFS(int x, int y) {
    for(int i=0;i<4;++i) {
        int newx=x+dx[i];
        int newy=y+dy[i];
        if(newx<0 || newx>matrix.size()-1 || newy<0 || newy>matrix.size()-1 || visited[newx][newy]) continue;
        // 주변 칸 중 1인 칸에 대해서만 dfs하여 한번에 하나씩 구역을 찾음
        if(matrix[newx][newy]==1) {
            result[indexx]++;
            visited[newx][newy]=true;
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
    visited.resize(N, vector<bool>(N, false));
    for(int i=0;i<N;++i) {
        cin >> s;
        for(int j=0;j<N;++j) {
            // 숫자문자를 형변환하면 아스키코드로 대체되므로 문자0을 먼저 빼준 후 형변환
            matrix[i][j]=(int)(s[j]-'0');
        }
    }
    // 첫원소는 미리 넣어주고 시작
    result.push_back(0);
    for(int x=0;x<N;++x) {
        for(int y=0;y<N;++y) {
            if(matrix[x][y]==1 && !visited[x][y]) {
                visited[x][y]=true;
                result[indexx]+=1;
                searchDFS(x, y);
                result.push_back(0);
                indexx++;
            }
        }
    }
    sort(result.begin(), result.end());
    // dfs 탐색이 끝날때마다 0원소를 넣어주므로 값이0인 원소는 지워준다 (답에서 제외)
    result.erase(result.begin());
    cout << result.size() << '\n';
    for(auto& o : result) {
        cout << o << '\n';
    }
    return 0;
}