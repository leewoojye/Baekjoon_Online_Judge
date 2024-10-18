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
    cout << v[0] << '\n';
    for (int i = 1; i < n; ++i) {
        if (v[i] == v[i-1]) continue;
        cout << v[i] << '\n';
    }
}