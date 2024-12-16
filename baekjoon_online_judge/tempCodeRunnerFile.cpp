#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <utility>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

vector<int> rangeMin;
vector<int> rangeMax;

struct segmentTree {
  vector<int> list;
  int n;
  int left,right;
  segmentTree(vector<int>& vc) {
    list=vc;
    this->n=list.size(); // 멤버변수는 곡 생성자에서 초기화해줌
    init(list, 1, 0, n-1);
  }
  // 세그먼트 트리 전처리
  // pair<min, max>
  pair<int,int> init(vector<int>& v, int node, int nodeLeft, int nodeRight) {
    if(nodeLeft==nodeRight) {
      rangeMin[node]=v[nodeLeft];
      rangeMax[node]=v[nodeLeft];
      return {v[nodeLeft], v[nodeLeft]};
    }
    int mid=(nodeLeft+nodeRight)/2;
    pair<int,int> nextLeft=init(v, node*2, nodeLeft, mid);
    pair<int,int> nextRight=init(v, node*2+1, mid+1, nodeRight);
    rangeMin[node]=min(nextLeft.first, nextRight.first);
    rangeMax[node]=max(nextLeft.second, nextRight.second);
    return {rangeMin[node], rangeMax[node]};
  }
  // left,right, nodeLeft, nodeRight, node가 주어졌을 때 노드구간내 최솟값 반환
  int queryMin(int node, int nodeLeft, int nodeRight) {
    if(nodeLeft==nodeRight) return rangeMin[node];
    if(nodeLeft>right || nodeRight<left) return INT_MAX;
    if(nodeLeft>=left && nodeRight<=right) return rangeMin[node];
    int mid=(nodeLeft+nodeRight)/2;
    return min(queryMin(node*2, nodeLeft, mid), queryMin(node*2+1, mid+1, nodeRight));
  }
  int queryMax(int node, int nodeLeft, int nodeRight) {
    if(nodeLeft==nodeRight) return rangeMax[node];
    if(nodeLeft>right || nodeRight<left) return -1;
    if(nodeLeft>=left && nodeRight<=right) return rangeMax[node];
    int mid=(nodeLeft+nodeRight)/2;
    return max(queryMax(node*2, nodeLeft, mid), queryMax(node*2+1, mid+1, nodeRight));
  }
  pair<int,int> queryInterface(int left, int right) {
    this->left=left-1;
    this->right=right-1;
    return {queryMin(1, 0, n-1), queryMax(1,0,n-1)};
  }
};

int main() {
  fastio;
  int N,M;
  cin >> N >> M;
  rangeMin.resize(4*N, INT_MAX);
  rangeMax.resize(4*N, -1);
  vector<int> input;
  int n;
  for(int i=0;i<N;++i) {
    cin >> n;
    input.push_back(n);
  }
  segmentTree* tree=new segmentTree(input);
  int l,r;
  for(int i=0;i<M;++i) {
    cin >> l >> r;
    pair<int,int> result=tree->queryInterface(l,r);
    cout << result.first << " " << result.second << '\n';
  }
  return 0;
}