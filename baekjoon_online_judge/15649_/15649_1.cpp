#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// m : 붙여야할 남은 정수갯수
// midret : 현재까지 만든 문자열(부분답)
// visited : 현재까지 정수들의 방문여부를 나타내는 불린벡터
void makeSequence(int m, string midret, vector<bool> visited) {
    if(m==0) {
      // 속도높이는 법 - endl 대신 '\n'을 쓴다.
        cout << midret << '\n';
        return;
    }
    // 벡터 생성자 또는 등호=를 이용해 주소전달이 아닌 값복사를 할 수 있다.
    // vector<bool> visited_copy(visited);
    for(int i=1;i<visited.size();++i) {
        // visited=visited_copy;
        if(!visited[i]) {
            // visited=visited_copy;
            visited[i]=true;
            string s=midret+to_string(i);
            makeSequence(m-1, s+" ", visited); // 마지막에 띄어쓰기가 포함된 것도 답으로 처리해주는듯..
            visited[i]=false; // 재귀함수에 복사된 벡터가 전달되므로 visited를 수정해도 변함이 없다.
        }
    }
    return;
}

int main()
{
    // auto start = std::chrono::high_resolution_clock::now();
    
    fastio;
    int N, M;
    cin >> N >> M;
    vector<bool> visited(N+1, false);
    makeSequence(M, "", visited);
    
    // auto end = std::chrono::high_resolution_clock::now();

    // 시간 계산
    // std::chrono::duration<double, std::milli> duration = end - start;
    // std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

    return 0;
}