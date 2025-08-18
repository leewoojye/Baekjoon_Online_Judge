#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int idx = 0, num = 0;
    for (int i = 0; i < 3; i++) {
        string s;
        cin >> s;
        if (s != "Fizz" && s != "Buzz" && s != "FizzBuzz") {
            idx = i;
            num = stoi(s);
        }
    }

    int next = num + (3 - idx);

    if (next % 15 == 0)
        cout << "FizzBuzz\n";
    else if (next % 3 == 0)
        cout << "Fizz\n";
    else if (next % 5 == 0)
        cout << "Buzz\n";
    else
        cout << next << "\n";

    return 0;
}