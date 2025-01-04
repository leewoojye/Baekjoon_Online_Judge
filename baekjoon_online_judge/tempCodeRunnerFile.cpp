#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

int main()
{
    int N,M;
    cin >> N >> M;
    queue<pair<int,int>> q;
    q.push({N,0});
    int ret;
    while(!q.empty()) {
        pair<int,int> node=q.front(); q.pop();
        int nodeValue=node.first;
        int nodeLength=node.second;
        if(nodeValue==M) {
            ret=nodeLength;
            break;
        }
        q.push({nodeValue+1,nodeLength+1});
        if(nodeValue>0) q.push({nodeValue-1,nodeLength+1});
        if(nodeValue*2<=M) q.push({nodeValue*2,nodeLength+1});
    }
    cout << ret;
    return 0;
}