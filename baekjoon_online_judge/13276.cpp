#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> getPartialMatch(string& s) {
  int size=s.size();
  vector<int> pi(size,0);
  int matched=0;
  for (int begin=1;begin<size;++begin) {
    matched=0;
    for(int i=0;i<begin+i<size;++i) {
      if(s[begin]==s[begin+i]) {
        matched++;
      } else {
        pi[begin+matched]=matched;
        break;
      }
    }
  }
  return pi;
}

int main() {
  fastio;
  string h, n1, n2;
  cin >> h;
  cin >> n1;
  cin >> n2;
  int begin=0;

  return 0;
}