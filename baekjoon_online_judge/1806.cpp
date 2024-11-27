#include <iostream>
#include <vector>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

int main() {
  fastio;
  int N,S;
  cin >> N >> S;
  vector<int> sequence(N);
  for(int i=0;i<N;++i) {
    cin >> sequence[i];
  }
  
  return 0;
}