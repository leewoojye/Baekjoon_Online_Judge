#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

void josephus(int n, int k)
{

    list<int> survivors;
    for (int i = 1; i <= n; i++)
        survivors.push_back(i);

    // 이번에 죽을 사람을 나타내는 포인터
    // 반복자 iterator는 포인터 역할을 한다.
    list<int>::iterator kill = survivors.begin();

    while (n > 2)
    {
        // 첫 번째 사람이 자살하고, erase()는 지운 원소의 다음 원소를 반환함.
        kill = survivors.erase(kill);
        // 리스트 끝에 포인터가 도달하면 처음을 다시 가리키게 함으로써 원형 리스트를 흉내내고 있음.
        if (kill == survivors.end())
            kill = survivors.begin();
        --n;

        // k-1번 다음 사람으로 옮김.
        for (int i = 0; i < k - 1; ++i)
        {
            ++kill;
            if (kill == survivors.end())
                kill = survivors.begin();
        }
    }

    cout << survivors.front() << " " << survivors.back() << endl;
}

int main() {

    josephus(6, 3);
    return 0;
}