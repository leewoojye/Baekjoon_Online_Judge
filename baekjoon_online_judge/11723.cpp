#include <iostream>
#include <string>
#include <bitset>
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
    return CMD_UNKNOWN; // 기본값
}

int main()
{
    fastio;
    int M;
    string cmd;
    // bitset<20> S(0);
    // bitset<20> S0(0);
    int S(0);
    int S0(0);
    int x;
    bool bit0;
    cin >> M;
    for(int i=0;i<M;++i) {
        cin >> cmd >> x;
        Command command=stringToCommand(cmd);
        switch(command) {
            case CMD_ADD:
            S |= (1<<x);
            break;
            case CMD_REMOVE:
            S0=(S>>x)-(1<<0);
            S0=(S0<<x);
            S=S0 | S;
            break;
            case CMD_CHECK:
            for(int i=0;i<20;++i) {
                cout << (S & (1<<0)) << '\n';
                S=(S>>1);
            }
            break;
            case CMD_TOGGLE:
            S ^= 0;
            break;
            case CMD_ALL:
            S |= ((1<<20)-1);
            break;
            case CMD_EMPTY:
            S &= (0<<19);
            break;
            default:
            break;
        }
    }
    return 0;
}