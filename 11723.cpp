#include <iostream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

enum Command {
    CMD_ADD,
    CMD_REMOVE,
    CMD_CHECK,
    CMD_TOGGLE,
    CMD_ALL,
    CMD_EMPTY,
    CMD_UNKNOWN
};

Command stringToCommand(const string& str) {
    if (str == "add") return CMD_ADD;
    if (str == "remove") return CMD_REMOVE;
    if (str == "check") return CMD_CHECK;
    if (str == "toggle") return CMD_TOGGLE;
    if (str == "all") return CMD_ALL;
    if (str == "empty") return CMD_EMPTY;
    return CMD_UNKNOWN;
}

int main()
{
    fastio;
    int M;
    string cmd;
    int S(0);
    int S0(0);
    int x;
    vector<bitset<1>> result;
    cin >> M;
    for(int i=0;i<M;++i) {
        cmd.clear();
        cin >> cmd;
        
        if(cmd=="all") {
            S |= ((1<<20)-1);
            continue;
        }
        if(cmd=="empty") {
            S=0;
            continue;
        }
        cin >> x;
        x-=1;
        Command command=stringToCommand(cmd);
        switch(command) {
            case CMD_ADD:
            S |= (1<<x);
            break;
            case CMD_REMOVE:
            // S0=(S>>x)-1;
            // S0=(S0<<x);
            // S=S0 | S;
            S = S & ~(1 << x);
            break;
            case CMD_CHECK:
            if(((1<<x) & S) != 0) {
                result.push_back(1);
            } else {
                result.push_back(0);
            }
            break;
            case CMD_TOGGLE:
            S ^= (1 << x);
            //S ^= 0;
            break;
            default:
            break;
        }
    }
    for(int i=0;i<result.size();++i) {
        cout << result[i] << '\n';
    }
    return 0;
}