#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using namespace std;

// 탐욕법 시도
int main() {
  fastio;
  int T;
  int length;
  int result;
  vector<int> inputList;
  cin >> T;
  for(int i=0;i<T;++i) {
    int ret=0;
    priority_queue<pair<int,int>,vector<pair<int, int>>, greater<>> pq;
    cin >> length;
    inputList.resize(length);
    for(int j=0;j<length;++j) {
      cin >> inputList[j];
    }
    for(int j=0;j<length-1;++j) {
      pq.push({inputList[j]+inputList[j+1], j});
    }
    while(pq.size()>1) {
      pair<int,int> min1=pq.top(); pq.pop();
      for(int j=0;j<pq.size();++j) {
      }
      ret+=min1.first;
    }
    cout << ret;
  }
  return 0;
}