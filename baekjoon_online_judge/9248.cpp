#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// comparator
// 객체를 함수처럼 쓴다 - (괄호) 연산자 오버로딩
struct Comparator {
  vector<string> _group;
  int _t;
  Comparator(vector<string>& group, int t) {
    _group=group;
    _t=t;
  }
  bool operator() (int a,int b) {
    if(_group[a+_t]==_group[b+_t]) return true;
    return _group[a+_t]<_group[b+_t];
  } 
};

// return suffix array
vector<string> getSuffixArray(const string& s) {
  // group[], perm[]
  int n=s.size();
  int t=1;
  vector<int> perm(n);
  vector<int> group(2*n, -1);
  for(int i=0;i<n;++i) perm[i]=i;
  for(int i=0;i<n;++i) group[i]=s[i];
  while(t>n) {
    // group 배열 만들기 (초기화)

    // newGroup을 만든다
  }
}

int main() {
  fastio;
  string input;
  cin >> input;

  return 0;
}