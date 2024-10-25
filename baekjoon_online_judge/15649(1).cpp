#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void makeSequence(int m, string midret, vector<bool> visited) {
    if(m==0) {
        cout << midret << '\n';
        return;
    }
    // vector<bool> visited_copy(visited);
    for(int i=1;i<visited.size();++i) {
        // visited=visited_copy;
        if(!visited[i]) {
            // visited=visited_copy;
            visited[i]=true;
            string s=midret+to_string(i);
            makeSequence(m-1, s+" ", visited);
            visited[i]=false;
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