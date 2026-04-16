#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// 문항조건 주의 !!! 집세우는 조합문제는 아님 집의 위치와 순서는 정해져있음
int N;
vector<vector<int>> houseRGB;
vector<vector<int>> dp;

// int vecToint(vector<bool> vec) {
//   int ret=0;
//   for(int i=0;i<vec.size();++i) {
//     if(!vec[i]) ret+=pow(2,i);
//   }
//   return ret;
// }

// rgb 각각 0,1,2
int chillMin(int loc, int prevRGB) {
  if(loc==N) return 0;
  int& ret=dp[loc][prevRGB];
  if(ret!=-1) return ret;
  ret=987654321;
  for(int i=0;i<3;++i) {
    if(i!=prevRGB) ret=min(ret,chillMin(loc+1,i)+houseRGB[loc][i]);
  }
  return ret;
}

int main() {
  fastio;
  cin >> N;
  houseRGB.resize(N,vector<int>(3));
  dp.resize(N,vector<int>(3, -1));
  int rgb;
  for(int i=0;i<N;++i) {
    for(int j=0;j<3;++j) {
      cin >> rgb;
      houseRGB[i][j]=rgb;
    }
  }
  int result=987654321;
  for(int i=0;i<3;++i) {
    result=min(result,chillMin(0,i));
  }
  cout << result;
  return 0;
}