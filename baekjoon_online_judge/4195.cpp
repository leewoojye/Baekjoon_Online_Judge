#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct DisjointSet {
  // string1의 부모 string2
  // 두 문자열이 서로 같으면 루트노드임.
  map<string, string> parent;
  // string이 속한 집합의 크기 int (집합트리의 높이 아님!)
  map<string, int> size;
  string find(string s) {
    if(s==parent[s]) return s;
    return parent[s]=find(parent[s]);
  }
  string merge(string s1, string s2) {
    s1=find(s1), s2=find(s2);
    if(s1==s2) return s1;
    if(size[s1]>size[s2]) swap(s1, s2);
    parent[s1]=s2;
    size[s2]=size[s1]+size[s2];
    return s2;
  }
};

int main() {
  fastio;
  int F;
  int C;
  cin >> C;
  DisjointSet set;
  for (int k = 0; k<C; ++k) {
    set.parent.clear();
    set.size.clear();
    cin >> F;
    for(int i=0;i<F;++i) {
      string s1,s2;
      cin >> s1 >> s2;
      if(set.parent.find(s1)==set.parent.end()) { set.parent[s1]=s1; set.size[s1]=1; }
      if(set.parent.find(s2)==set.parent.end()) { set.parent[s2]=s2; set.size[s2]=1; }
      cout << set.size[set.merge(s1,s2)] << '\n';
    }
  }
  return 0;
}