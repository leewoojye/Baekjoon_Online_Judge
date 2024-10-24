#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

// bool visited[9]; // visited[0]~visited[8]
// bool visitedinit[9];
// vector<bool> visited;

string makeSequence(int m, int i, vector<bool> visited) {
    if(m==0) {
        return "";
    }
    visited[i]=true;
    vector<bool> visited_copy=visited;
    for(int j=1;j<9;++j) {
        //cout << to_string(i) + " ";
        visited_copy=visited;
        if(!visited[j]) {
            visited_copy[j]=true;
            return to_string(j) + " " + makeSequence(m-1, i, visited_copy);
        }
    }
    return "";
}

int main()
{
    fastio;
    int N, M;
    cin >> N >> M;
    vector<bool> visited(9);
    for(int i=0;i<=8;++i) {
        if(i>N) {
            visited[i]=true;
        } else {
            visited[i]=false;
        }
    }
    for(int i=1;i<=N;++i) {
        cout << to_string(i) << " ";
        visited[i]=true;
        cout << makeSequence(M-1, i, visited) << endl;
    }

    return 0;
}