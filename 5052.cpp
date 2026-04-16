#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

struct TrieNode {
  vector<TrieNode*> children;
  bool terminal;
  bool hasChild; // 현재 노드가 자식이 있는지 여부를 저장. 자식이 있으면 어떤 문자열의 접두어이므로 문제에서 NO를 반환해야한다
  TrieNode() {
    // 함수가 아닌 구조체 내부에서는 생성자 안에서 초기화작업을 해준다
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
  // 주어진 문자 key를 현재 노드의 맴버로(구체적으론 자식을 나타내는 배열) 집어넣는다
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
      list[j]=s; // 문자열 s를 '복사'전달하였으니 insert() 인자로는 s가 아닌 list의 주소를 전달한다
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