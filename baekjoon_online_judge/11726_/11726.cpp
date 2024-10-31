#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// 모듈러 연산
vector<long long> dp;

long long squareDp(int n) {
    if(n==2) {
        return 2;
    } else if (n==1) {
        return 1;
    }
    long long case1;
    long long case2;
    if(dp[n-1]!=-1) {
        case1=dp[n-1];
    } else {
        dp[n-1]=case1=squareDp(n-1);
    }
    if(dp[n-2]!=-1) {
        case2=dp[n-2];
    } else {
        dp[n-2]=case2=squareDp(n-2);
    }
    return (case1%10007+case2%10007)%10007;
}

int main()
{
    fastio;
    int n;
    cin >> n;
    long long result;
    dp.resize(n, -1);
    result=squareDp(n)%10007;
    cout << result;
    //cout << squareDp(n);

    return 0;
}