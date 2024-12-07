#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct DisjointSet {
  // string1의 부모 string2
  map<string, string> parent;
  // string이 속한 집합의 크기 int
  map<string, int> size;
  string find(string s) {
    if(s==parent[s]) return s;
    return parent[s]=find(parent[s]);
  }
  void merge(string s1, string s2) {
    string s1=find(s1), s2=find(s2);
    if(s1==s2) return;
    if(size[s1]>size[s2]) swap(s1, s2);
    parent[s1]=s2;
    if(size[s1]==size[s2]) size[s2]+=1;
  }
};

int main() {
  fastio;
  int F;
  cin >> F;
  for(int i=0;i<F;++i) {
    string s1,s2;
    cin >> s1 >> s2;
  }
  return 0;
}