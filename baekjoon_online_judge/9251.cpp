#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int cache[1001][1001];
int size1,size2;
string s1,s2;
int maxLCS(int index1, int index2) {
  if(index1>=size1 || index2>=size2) return 0;
  int& ret=cache[index1][index2];
  if(ret!=-1) return ret;
  int caseIncluded;
  if(s1[index1]==s2[index2]) {
    // index1 문자를 포함하는 경우, 포함하지 않는 경우 중 최대값 반환
    caseIncluded=max(maxLCS(index1+1,index2+1)+1,maxLCS(index1+1,index2+1));
  } else {
    caseIncluded=-1;
  }
  return ret=max(max(caseIncluded,maxLCS(index1,index2+1)),maxLCS(index1+1,index2));
}

int main() {
  fastio;
  cin >> s1 >> s2;
  size1=s1.length();
  size2=s2.length();
  for(int i=0;i<1001;++i) {
    for(int j=0;j<1001;++j) {
      cache[i][j]=-1;
    }
  }
  int result=maxLCS(0,0);
  cout << result;
  return 0;
}