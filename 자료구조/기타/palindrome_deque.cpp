#include <iostream>
#include <vector>
#include <string>
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

void print_deque(vector<char>& deque) {
  for(int i=0;i<deque.size();i++) {
    if(deque[i]!='\0') cout << deque[i] << "|";
  }
  cout << '\n';
  return;
}

bool deque_is_empty(vector<char>& deque) {
  for(int i=0;i<deque.size();i++) {
    if(deque[i]!='\0') return false;
  }
  return true;
}

bool deque_is_full(vector<char>& deque) {
  for(int i=0;i<deque.size();i++) {
    if(deque[i]=='\0') return false;
  }
  return true;
}

int main() {
  fastio;
  string s;
  bool flag = true;
  cout << "문자열을 입력하시오: ";
  cin >> s;
  vector<char> deque(s.length(),'\0');
  int front = -1;
  int rear = 0;

  do {
    deque[rear]=s[rear];
    rear++;
    cout << "DEQUE(front=" << 0 << " rear=" << rear << ")" << " = ";
    print_deque(deque);
  } while(!deque_is_full(deque));

  while(!deque_is_empty(deque)) {
    if(flag==true && deque[rear-1]!=deque[front+1]) flag=false;
    deque[front+1]='\0';
    front++;
    if(deque_is_empty(deque)) break;
    cout << "DEQUE(front=" << front+1 << " rear=" << rear << ")" << " = ";
    print_deque(deque);
    deque[rear-1]='\0';
    rear--;
    cout << "DEQUE(front=" << front+1 << " rear=" << rear << ")" << " = ";
    print_deque(deque);
  }

  if(!flag) {
    cout << "회문이 아님" << '\n';
    return 0;
  }
  cout << "회문" << '\n';
  return 0;
}