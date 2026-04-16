#include <iostream>
#include <vector>
#include <algorithm>  // sort()를 사용하려면 이 헤더가 필요합니다.
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int count, A;
  cin >> count;
  vector<int> list;
  for(int i=0;i<count;++i) {
    cin >> A;
    list.push_back(A);
  }
  sort(list.begin(), list.end());
  if(count==1) {
    cout << A*A;
    return 0;
  }
  cout << list.front()*list.back();
  return 0;
}