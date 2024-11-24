#include <iostream>
#include <map>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  map<string, bool> myMap;
  map<string, bool>::iterator p;
  int N,M;
  int count=0;
  string s;
  cin >> N >> M;
  for(int i=0;i<N;++i) {
    cin >> s;
    myMap.insert({s, false});
  }
  for(int i=0;i<M;++i) {
    cin >> s;
    p=myMap.find(s);
    if(p!=myMap.end()) {
      p->second=true;
      count++;
    }
  }
  cout << count << '\n';
  for(p = myMap.begin(); p != myMap.end(); ++p) {
    if(p->second) {
      cout << p->first << '\n';
    }
  }
  return 0;
}