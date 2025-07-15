#include <iostream>
using namespace std;

int z(int n, int r, int c) {
    if (n == 0) return 0;
    int half = 1 << (n - 1);
    int quad = (r >= half ? 2 : 0) + (c >= half ? 1 : 0);
    return quad * (half * half) + z(n - 1, r % half, c % half);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N, r, c;
    cin >> N >> r >> c;
    cout << z(N, r, c) << '\n';
    return 0;
}