#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int N;
  cin >> N;
  vector<int> waitingLine(N, 0);
  for(int w=0;w<N;++w) {
    cin >> waitingLine[w];
  }
  sort(waitingLine.begin(), waitingLine.end());
  int sum=0;
  int snowball=0;
  for(int i=0;i<N;++i) {
    snowball+=waitingLine[i];
    sum+=snowball;
  }
  cout << sum;
  return 0;
}