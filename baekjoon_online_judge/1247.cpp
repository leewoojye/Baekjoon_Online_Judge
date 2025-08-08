#include <iostream>
using namespace std;

using int128 = __int128;

void print_sign(int128 sum) {
    if (sum > 0) cout << "+\n";
    else if (sum < 0) cout << "-\n";
    else cout << "0\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int t = 0; t < 3; t++) {
        int n;
        cin >> n;
        int128 sum = 0;
        for (int i = 0; i < n; i++) {
            long long x;
            cin >> x;
            sum += x;
        }
        print_sign(sum);
    }

    return 0;
}