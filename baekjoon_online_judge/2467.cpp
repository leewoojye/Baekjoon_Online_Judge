#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;

pair<int, int> resultPair;

void findLiquid(vector<int> list) {
    if(list[0]>0 && list[list.size()-1]>0) {
        resultPair.first = list[0];
        resultPair.second = list[1];
        return;
    }
    if(list[0]<0 && list[list.size()-1]<0) {
        resultPair.first = list[list.size()-2];
        resultPair.second = list[list.size()-1];
        return;
    }
    //
    for(int j=0;j<=list.size()-1;++j) {
        if(list[j]>0) {
            break;
        }
            if(abs(list[0])<abs(list[list.size()-1])) {
                for(int i=list.size()-1;i>=0;--i) {
                    if(list[i]<0) {
                        break;
                    }
                    if(list[j]+list[list.size()-1]<0) {
                        resultPair.first = list[j];
                        resultPair.second = abs(list[j]+list[i])>abs(list[j]+list[i+1]) ? list[i+1] : list[i];
                        break;
                    }
                }
            } else {
                for(int i=list.size()-1;i>=0;--i) {
                    if(list[i]<0) {
                        break;
                    }
                    if(list[j]+list[list.size()-1]>0) {
                        resultPair.first = list[j];
                        resultPair.second = abs(list[j]+list[i])>abs(list[j]+list[i+1]) ? list[i+1] : list[i];
                        break;
                    }
                }
            }
        
    }
    return;
}

int main()
{
    fastio;
    int N;
    cin >> N;
    vector<int> list(N);
    for(auto& e : list) {
        cin >> e;
    }
    findLiquid(list);
    cout << resultPair.first << resultPair.second;
    return 0;
}