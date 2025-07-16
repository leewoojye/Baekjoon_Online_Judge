#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
  fastio;
  vector<pair<int,string>> orderedList;
  int N;
  cin >> N;
  pair<int,string> p;
  pair<int,string> tmp;
  for(int n=0;n<N;++n) {
    cin >> p.first >> p.second;
    // orderedList.push_back(p);
    for(int i=orderedList.size()-1;i>0;--i) {
      if(orderedList[i].first<orderedList[i-1].first) {
        // tmp=orderedList[i-1];
        // orderedList[i-1]=orderedList[i];
        // orderedList[i]=tmp;
        continue;
      }
      orderedList.insert(orderedList.begin()+i+1,p);
    }
  }
  for(int i=0;i<orderedList.size();++i) {
    cout << orderedList[i].first << " " << orderedList[i].second << '\n';
  }
  return 0;
}