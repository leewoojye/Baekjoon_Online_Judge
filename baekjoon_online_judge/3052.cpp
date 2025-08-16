#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> remainders;  // 중복을 허용하지 않는 set 사용
    for (int i = 0; i < 10; i++) {
        int num;
        cin >> num;
        remainders.insert(num % 42);  // 나머지를 set에 삽입
    }
    cout << remainders.size() << "\n";  // 서로 다른 나머지 개수 출력
    return 0;
}