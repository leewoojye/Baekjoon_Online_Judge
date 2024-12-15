#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

struct TrieNode {
  vector<TrieNode*> children;
  bool terminal;
  bool hasChild;
  TrieNode() {
    // 함수가 아닌 구조체 내부에서는 생성자 안에서 초기화작업을 해줌
    children.resize(10, nullptr);
    this->terminal=false;
    this->hasChild=false;
  }
  // find() : 부분문자열 노드를 반환, 없으면 nullptr를 반환
  TrieNode* find(const char* key) {
    if(*key==0) return this;
    if(this->children[*key-'0']==nullptr) return nullptr;
    return children[*key-'0']->find(key+1);
  }
  // insert() : 인자로 주어진 문자열을 트라이에 삽입
  // 주어진 문자를 현재 노드의 자식으로 집어넣는다
  void insert(const char* key) {
    if(*key==0) { this->terminal=true; return; }
    if(this->children[*key-'0']==nullptr) {
      TrieNode* node=new TrieNode();
      this->children[*key-'0']=node;
      this->hasChild=true;
      node->insert(key+1);
    } else {
      this->hasChild=true;
      children[*key-'0']->insert(key+1); // 현재노드자신의 insert()가 아닌 자식의 insert()함수를 재귀호출함
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
    vector<string> list(n);
    TrieNode* node=new TrieNode();
    for(int j=0;j<n;++j) {
      cin >> s;
      list[j]=s;
      node->insert(&list[j][0]);
    }
    bool flag=true;
    for(int j=0;j<n;++j) {
      TrieNode* p=node->find(&list[j][0]);
      if(p->hasChild) { cout << "NO" <<'\n'; flag=false; break; }
    }
    if(flag) cout << "YES" << '\n';
  }
  return 0;
}