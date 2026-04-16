#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int lengths[3];

int main() {
  fastio;
  int maxlength;
  vector<string> result;
  while(1) {
    int pow1=0,pow2=0;
    for(int i=0;i<3;++i) {
      cin >> lengths[i];
      if(lengths[0]==0) break;
      if(i==0) { maxlength=lengths[0]; continue; }
      // if(i!=0 && lengths[i]>lengths[i-1]) maxlength=lengths[i];
      maxlength=max(lengths[i],maxlength); // 윗줄 이걸로 바꿨더니 맞음.. 뭐임?
    }
    if(lengths[0]==0) break;
    pow1=maxlength*maxlength;
    for(int i=0;i<3;++i) {
      if(lengths[i]<maxlength) pow2+=(lengths[i]*lengths[i]);
    }
    if(pow1==pow2) { result.push_back("right"); continue; }
    result.push_back("wrong");
  }
  for(int i=0;i<result.size();++i) {
    cout << result[i] << '\n';
  }
  return 0;
}