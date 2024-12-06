#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int main() {
  fastio;
  int N;
  cin >> N;
  vector<vector<int>> matrix(N, vector<int>(N, INT_MAX-1000));
  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      int input;
      cin >> input;
      if(input==1) matrix[i][j]=1;
    }
  }

  for(int k=0;k<N;++k) {
    for(int e1=0;e1<N;++e1) {
      for(int e2=0;e2<N;++e2) {
        matrix[e1][e2]=min(matrix[e1][e2], matrix[e1][k]+matrix[k][e2]);
      }
    }
  }

  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      if(i==j) {
        cout << 1 << " ";
        continue;
      }
      if(matrix[i][j]==INT_MAX-1000) {
        cout << 0 << " ";
        continue;
      }
      cout << 1 << " ";
    }
    cout << '\n';
  }
  return 0;
}