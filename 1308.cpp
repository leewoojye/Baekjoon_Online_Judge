#include <iostream>
using namespace std;

int days_in_month[13] = {0,
    31,28,31,30,31,30,31,31,30,31,30,31
};

bool is_leap(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) return true;
            return false;
        }
        return true;
    }
    return false;
}

int count_days(int y, int m, int d) {
    int days = 0;
    for (int i = 1; i < y; ++i) {
        days += 365;
        if (is_leap(i)) days += 1;
    }
    for (int i = 1; i < m; ++i) {
        days += days_in_month[i];
        if (i == 2 && is_leap(y)) days += 1;
    }
    days += d;
    return days;
}

int main() {
    int y1, m1, d1, y2, m2, d2;
    cin >> y1 >> m1 >> d1;
    cin >> y2 >> m2 >> d2;

    if(y2 - y1 > 1000 ||
       (y2 - y1 == 1000 && (m2 > m1 || (m2 == m1 && d2 >= d1)))) {
        cout << "gg\n";
        return 0;
    }
    int dday = count_days(y2, m2, d2) - count_days(y1, m1, d1);
    cout << "D-" << dday << '\n';
    return 0;
}