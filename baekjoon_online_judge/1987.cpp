#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<char>> matrix;
struct Node {
  pair<int, int> p;
  vector<Node*> children;
};

void makeTree(vector<bool> alpha, Node* node) {

  alpha[matrix[node->p.first][node->p.second]-'A']=true;

  // matrix[][]에 대해 첫인자가 세로방향이고 두번째인자가 가로방향 인덱스임.
  // x축으로 -1 이동
  if(node->p.second>0 && !alpha[matrix[node->p.first][node->p.second-1]-'A']) {
    Node* n=new Node;
    n->p = {node->p.first, node->p.second-1};
    node->children.push_back(n);
    makeTree(alpha, n);
  }
  // x축으로 +1 이동
  if(node->p.second<matrix[0].size()-1 && !alpha[matrix[node->p.first][node->p.second+1]-'A']) {
    Node* n=new Node;
    n->p = {node->p.first, node->p.second+1};
    node->children.push_back(n);
    makeTree(alpha, n);
  }
  // y축으로 -1 이동
  if(node->p.first>0 && !alpha[matrix[node->p.first-1][node->p.second]-'A']) {
    Node* n=new Node;
    n->p = {node->p.first-1, node->p.second};
    node->children.push_back(n);
    makeTree(alpha, n);
  }
  // y축으로 +1 이동
  if(node->p.first<matrix.size()-1 && !alpha[matrix[node->p.first+1][node->p.second]-'A']) {
    Node* n=new Node;
    n->p = {node->p.first+1, node->p.second};
    node->children.push_back(n);
    makeTree(alpha, n);
  }
  return;
}

int getHeight(Node* root) {
  int h=0;
  for(int i=0;i<root->children.size();++i) {
    h=max(h, 1+getHeight(root->children[i]));
  }
  return h;
}

int main() {
  fastio;
  int R, C;
  string s;
  cin >> R >> C;
  matrix.resize(R, vector<char>(C));
  for(int i=0;i<R;++i) {
    cin >> s;
    for(int j=0;j<C;++j) {
      matrix[i][j]=s[j];
    }
  }
  vector<bool> alpha(26, false);
  Node* n=new Node;
  n->p = {0, 0};
  makeTree(alpha, n);
  cout << getHeight(n)+1;

  for (Node* child : n->children) {
    delete child;
  }
  delete n;

  return 0;
}