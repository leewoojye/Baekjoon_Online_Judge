#include <iostream>
#include <map>
#include <queue>
#include <cmath>
using namespace std;
class State {
  vector<State> getAdjacent() const;
  // 연산자오버로딩 형식
  // <반환타입> operator <연산자>(<매개변수들>);
  bool operator < (const State& rhs) const;
  bool operator == (const State& rhs) const;
};
int sgn(int x) { if(!x) return 0; return x>0 ? 1 : -1; }
int incr(int x) { if(x<0) return x-1; return x+1; }

int cidirectional(State start, State finish) {
  map<State, int> c;
  queue<State> q;
  if(start==finish) return 0;
  q.push(start); c[start]=1;
  q.push(finish); c[finish]=-1;

  while(!q.empty()) {
    State here=q.front();
    q.pop();
    vector<State> adjacent=here.getAdjacent();
    for(int i=0;i<adjacent.size();++i) {
      // map<키 타입, 값 타입>
      // find()는 해당 키가 맵에 존재하면 그 키에 대한 반복자(iterator)를 반환하고, 만약 키가 존재하지 않으면 c.end()를 반환
      map<State, int>::iterator it=c.find(adjacent[i]);
      // end()는 실제로 "끝"을 나타내지만, 그 자체로는 값이 아니라 "끝"의 위치를 나타내므로 직접 참조해서 값을 출력하면 오류가 발생
      if(it==c.end()) {
        c[adjacent[i]]=incr(c[here]);
        q.push(adjacent[i]);
      }
      // 가운데서 만난 경우
      else if(sgn(it->second)!=sgn(c[here])) {
        return abs(it->second)+abs(c[here])-1;
      }
    }
  }
  // 답을 찾지 못한 경우
  return -1;
}