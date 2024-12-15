#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

struct TrieNode {
  vector<TrieNode*> children;
  bool terminal;
  TrieNode() {
    // 함수가 아닌 구조체 내부에서는 생성자 안에서 초기화작업을 해줌
    children.resize(10, nullptr);
    this->terminal=false;
  }
  // find() : 부분문자열 노드를 반환, 없으면 nullptr를 반환
  TrieNode* find(const char* key) {
    if(*key==0) return this;
    if(this->children[*key-'0']==nullptr) return nullptr;
    return find(key+1);
  }
  // insert() : 인자로 주어진 문자열을 트라이에 삽입
  void insert(const char* key) {
    if(*key==0) { this->terminal=true; return; }
    if(this->children[*key-'0']==nullptr) {
      TrieNode* node=new TrieNode();
      node->insert(key+1);
    } else {
      insert(key+1);
    }
  }
};

int main() {
  fastio;
  int t,n;
  cin >> t;
  for(int i=0;i<t;++i) {
    cin >> n;
    string s;
    for(int j=0;j<n;++n) {
      TrieNode* node=new TrieNode();
      cin >> s;
      node->insert(&s[0]);
    }
  }
  return 0;
}