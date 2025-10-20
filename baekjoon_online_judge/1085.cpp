#include <iostream>
using namespace std;

int main() {
    int x, y, w, h;
    cin >> x >> y >> w >> h;
    int min_dist = min(min(x, w - x), min(y, h - y));
    cout << min_dist << endl;
    return 0;
}