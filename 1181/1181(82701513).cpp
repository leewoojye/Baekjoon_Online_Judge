#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

int main() {
    fastio;

    int n;
    cin >> n;
    vector<string> v(n);
    for (auto& e : v) cin >> e;
    sort(v.begin(), v.end(), [](const string& a, const string& b) {
        if (a.size() == b.size()) return a < b;
        return a.size() < b.size();
    });
    // c++ 람다 표현식
    // [capture](parameters) -> return_type { 캡쳐는 외부변수에 접근하는 방법을 정해줌. 예) 파라미터가 아닌 외부변수를 참조로 받을지 값을 복사할지
    // // 함수 본체
    // }
    cout << v[0] << '\n';
    for (int i = 1; i < n; ++i) {
        if (v[i] == v[i-1]) continue;
        cout << v[i] << '\n';
    }
}