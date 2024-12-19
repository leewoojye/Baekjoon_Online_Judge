#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  int N;
  cin >> N;
  vector<int> result(101);
  result[0]=0;
  result[1]=9;
  int midValue;
  for(int i=2;i<=N;++i) {
    midValue=result[i-1];
    midValue+=result[i-2]*
  }
  return 0;
}