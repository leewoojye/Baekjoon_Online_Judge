// #include <iostream>
// #include <vector>
// #include <utility>
// #include <cmath>
// using namespace std;
// #define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// int func(int n) {
//   if(n==0) return 1;
//   return 6*(pow(2,n)-1);
// }

// int main(int argc, const char** argv) {
//   fastio;
//   int N;
//   cin >> N;
//   if(N==1) {cout << 1 << '\n'; return 0;}
//   int sum=1;
//   int count=1;
//   while(1) {
//     sum+=func(count);
//     if(sum>=N) {break;}
//     count++;
//   }
//   cout << count+1 << '\n';
//   return 0;
// }

#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int layer = 1;   // 층 수 (시작은 1)
    int maxNum = 1;  // 해당 층의 최대 방 번호

    while (N > maxNum) {
        maxNum += 6 * layer;
        layer++;
    }

    cout << layer << '\n';
    return 0;
}
