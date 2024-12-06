#include <iostream>
#include <vector>
#include <climits>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int main() {
  fastio;
  int N;
  vector<vector<int>> matrix(N, vector<int>(N, INT_MAX));
  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin >> matrix[i][j];
    }
  }
  cout << INT_MAX;
  return 0;
}