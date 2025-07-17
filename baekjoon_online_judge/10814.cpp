#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  vector<vector<pair<int,string>>> matrix(201);
  int N;
  cin >> N;
  pair<int,string> p;
  for(int n=0;n<N;++n) {
    cin >> p.first >> p.second;
    matrix[p.first].push_back(p);
  }
  for(int i=1;i<201;++i) {
    for(int j=0;j<matrix[i].size();++j) {
      cout << matrix[i][j].first << " " << matrix[i][j].second << '\n';
    }
  }
  return 0;
}