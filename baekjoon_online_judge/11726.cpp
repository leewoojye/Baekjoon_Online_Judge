#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

vector<int> dp;

int squareDp(int n) {
    if(n==2) {
        return 2;
    } else if (n==1) {
        return 1;
    }
    int case1;
    int case2;
    if(dp[n-1]!=-1) {
        case1=dp[n-1];
    } else {
        case1=squareDp(n-1);
        dp[n-1]=case1;
    }
    if(dp[n-2]!=-1) {
        case2=dp[n-2];
    } else {
        case2=squareDp(n-2);
        dp[n-2]=case2;
    }
    return case1+case2;
}

int main()
{
    fastio;
    int n;
    cin >> n;
    int result;
    dp.resize(n, -1);
    result=squareDp(n)%10007;
    cout << result;

    return 0;
}