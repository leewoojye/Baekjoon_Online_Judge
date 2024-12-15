#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int N,M;
  cin >> N >> M;
  map<string, 0> list1(N);
  map<string> list2(M);
  for(int i=0;i<N;++i) {
    cin >> list1[i];
  }  
  for(int i=0;i<M;++i) {
    cin >> list2[i];
  }
  return 0;
}