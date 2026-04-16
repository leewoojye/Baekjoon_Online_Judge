#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int N;
  cin >> N;
  vector<pair<int,int>> list(N);
  for(int i=0;i<N;++i) {
    // 끝나는시각-시작시각 순으로 저장
    cin >> list[i].second >> list[i].first;
  }
  // 일찍 끝나는 순으로 정렬
  sort(list.begin(),list.end());
  int count = 1;
  int start = list[0].first;
  for(int i=1;i<N;++i) {
    if(list[i].second>=start) {
      start = list[i].first;
      count++;
    }
  }
  cout << count;
  return 0;
}