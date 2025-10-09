#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string bin, result;
    cin >> bin;

    while (bin.size() % 3 != 0)
        bin = '0' + bin;

    for (int i = 0; i < bin.size(); i += 3) {
        int oct = (bin[i] - '0') * 4 + (bin[i+1] - '0') * 2 + (bin[i+2] - '0');
        result += (oct + '0');
    }

    int pos = result.find_first_not_of('0');
    if (pos != string::npos)
        result = result.substr(pos);
    else
        result = "0";
    cout << result << '\n';
    return 0;
}