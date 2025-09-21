#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> dots(N,0);
  for(int i=0;i<N;++i) {
    cin >> dots[i];
  }
  
  return 0;
}