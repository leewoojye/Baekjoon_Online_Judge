#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> dp;
vector<pair<int,int>> vec;
// 배낭물품목록인 큐와 남은 배낭부피가 주어졌을 때, 최대가치를 반환
int maxValue(int index, int leftOver) {
  if(index==vec.size()) return 0;
  pair<int,int> front=vec[index];
  int weight=front.first;
  int value=front.second;
  // if(index==vec.size()-1 && leftOver<weight) return 0;
  int& ret=dp[index][leftOver];
  if(ret!=-1) return ret;
  leftOver>=weight ? ret=max(maxValue(index+1,leftOver),maxValue(index+1,leftOver-weight)+value) : ret=maxValue(index+1,leftOver);
  return ret;
}

int main() {
  fastio;
  int N,K;
  cin >> N >> K;
  int w,v;
  dp.resize(N,vector<int>(K+1,-1));
  for(int i=0;i<N;++i) {
    cin >> w >> v;
    vec.push_back({w,v});
  }
  cout << maxValue(0,K);
  return 0;
}