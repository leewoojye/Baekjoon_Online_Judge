#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<double> scores(n);
    double maxScore = 0;

    for (int i = 0; i < n; i++) {
        cin >> scores[i];
        if (scores[i] > maxScore) {
            maxScore = scores[i];
        }
    }

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (scores[i] / maxScore) * 100;
    }

    double average = sum / n;
    cout << fixed;
    cout.precision(6);
    cout << average << endl;

    return 0;
}
