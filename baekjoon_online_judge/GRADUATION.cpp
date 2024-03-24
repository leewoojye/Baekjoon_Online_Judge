#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <bit>
#include <bitset>
#include <cstdint>
using namespace std;

const int INF = 987654321;
int n,k,m,l;

// i번째 과목의 선수과목의 집합
int prerequisite[MAXN];

// classes[i] : i번째 학기에 개설되는 과목의 집합, 과목들의 집합을 int형 정수로 표현 가능함.
// 예. {1,2,3} -> 이진수 1110 -> 십진수 14
int classes[10];
int cache[10][1<<MAXN];

int bitCount(int x) {
    if(x==0) return 0;
    return x%2 + bitCount(x/2);
}

// 이번 학기가 semester고, 지금까지 들은 과목의 집합이 taken일 때, k개 이상의 과목을 모두 들으려고 할 때 필요한 학기 수를 반환.
int graduate(int semester, int taken) {
    if (bitCount(taken)>=k) return 0;
    if (semester==m) return INF;

    // 메모이제이션
    int& ret = cache[semester][taken];
    if (ret != -1) return ret;
    ret = INF;

    // 이번 학기에 들을 수 있는 과목 중 아직 듣지 않은 과목들을 찾음.
    int canTake = (classes[semester & ~taken]);

    // 선수 과목을 다 듣지 않은 과목들을 걸러냄.
    for (int i = 0; i<n; ++i) {
        if ((canTake & (1<<i)) && (taken & prerequisite[i]) != prerequisite[i]) canTake &= ~(1<<i);
    }

    // 이 집합의 모든 부분집합을 순회함.
    for (int take = canTake; take>0; take=((take-1) & canTake)) {
        if (bitCount(take)>l) continue;
        ret = min(ret, graduate(semester+1, taken | take) + 1);
    }

    // 이번 학기에 아무것도 듣지 않을 경우
    ret = min(ret, graduate(semester + 1, taken));
    return ret;
}

int main() {
    return 0;
}