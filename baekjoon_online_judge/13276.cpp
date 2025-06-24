#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> getPartialMatch(string& s) {
  int size=s.size();
  vector<int> pi(size,0);
  pi[0]=0;
  int matched=0;
  for (int begin=1;begin+matched<size;) { // 종료조건: begin+matched<size
    for(int i=0;begin+i<size;++i) {
      if(s[i]==s[begin+i]) {
        matched++;
        pi[begin+matched-1]=matched;
      } else {
        if(matched==0) { begin++; break; }
        begin+=matched-pi[matched-1];
        matched=pi[matched-1];
        break;
      }
    }
  }
  return pi;
}

vector<int> kmpSearch(vector<int>& pi, string& h, string& n) {
  vector<int> ret;
  int matched=0;
  int begin=0;
  while(begin+n.size()<=h.size()) {
    for(int i=0;begin+i<h.size();++i) {
      if(h[begin+i]==n[i]) {
        matched++;
        if(matched==n.size()) {
          ret.push_back(begin); 
          begin+=matched-pi[matched-1];
          // matched=pi[matched-1];
          break;
        }
      } else {
        if(matched==0) { begin++; break; }
        else { 
          // if(matched==n.size()) ret.push_back(begin); 
          begin+=matched-pi[matched-1];
          matched=pi[matched-1];
          break;
        }
      }
    }
  }
  return ret;
}

int main() {
  fastio;  
  string h, n1, n2;
  cin >> h;
  cin >> n1; // 시작문자열
  cin >> n2; // 끝문자열
  // testcode
  // vector<int> pi=getPartialMatch(h);
  // // for(int i=0;i<h.size();++i) {
  // //   cout << pi[i] << '\n';
  // // }
  vector<int> pi_n1=getPartialMatch(n1);
  vector<int> pi_n2=getPartialMatch(n2);
  // 짚더미 문자열 h에 대해 n1,n2의 출연빈도를 각각 구한다.
  vector<int> n1Index=kmpSearch(pi_n1, h, n1);
  vector<int> n2Index=kmpSearch(pi_n2, h, n2);
  // for(int i=0;i<n1Index.size();++i) {
  //   cout << n1Index[i] << " ";
  // }
  vector<string> ret;
  for(int i=0;i<n1Index.size();++i) {
    for(int j=0;j<n2Index.size();++j) {
      if(n1Index[i]<=n2Index[j] && ) ret.push_back(h.substr(i,j-i+1));
    }
  }
  cout << ret << '\n';
  return 0;
}