#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    unordered_map<string, int> value = {
        {"black", 0}, {"brown", 1}, {"red", 2}, {"orange", 3},
        {"yellow", 4}, {"green", 5}, {"blue", 6}, {"violet", 7},
        {"grey", 8}, {"white", 9}
    };
    unordered_map<string, long long> multiplier = {
        {"black", 1}, {"brown", 10}, {"red", 100}, {"orange", 1000},
        {"yellow", 10000}, {"green", 100000}, {"blue", 1000000},
        {"violet", 10000000}, {"grey", 100000000}, {"white", 1000000000}
    };

    string a, b, c;
    cin >> a >> b >> c;

    long long res = (value[a] * 10 + value[b]) * multiplier[c];
    cout << res << endl;
    return 0;
}