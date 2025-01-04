#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    // 각 노드들의 방문여부를 저장하는 불린배열
    bool visited[100001];
    fill(visited, visited + 100001, false);
    int N,M;
    cin >> N >> M;
    queue<pair<int,int>> q;
    q.push({N,0});
    int ret;
    while(!q.empty()) {
        pair<int,int> node=q.front(); q.pop();
        int nodeValue=node.first;
        visited[nodeValue]=true;
        int nodeLength=node.second;
        if(nodeValue==M) {
            ret=nodeLength;
            break;
        }
        if(nodeValue<M && nodeValue+1<=100000 && !visited[nodeValue+1]) q.push({nodeValue+1,nodeLength+1});
        if(nodeValue>0 && !visited[nodeValue-1]) q.push({nodeValue-1,nodeLength+1});
        if(nodeValue<M && nodeValue*2<=100000 && !visited[nodeValue*2]) q.push({nodeValue*2,nodeLength+1});
    }
    cout << ret;
    return 0;
}