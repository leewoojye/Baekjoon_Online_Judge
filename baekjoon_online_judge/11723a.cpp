#include <iostream>
#include <string>
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

int main() {
    fastio;
    int M;
    string cmd;
    int S = 0;
    int x;
    
    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> cmd;
        
        if (cmd == "all") {
            S |= ((1 << 20) - 1);  // 모든 비트 1로 설정
            continue;
        }
        if (cmd == "empty") {
            S = 0;  // 모든 비트 0으로 설정
            continue;
        }
        
        cin >> x;
        x -= 1;
        Command command = stringToCommand(cmd);
        
        switch (command) {
            case CMD_ADD:
                S |= (1 << x);
                break;
            case CMD_REMOVE:
                S = S & ~(1 << x);
                break;
            case CMD_CHECK:
                // check 결과를 즉시 출력
                // 입력값 다 받고 마지막에 출력됨 how?
                if ((S & (1 << x)) != 0) {
                    cout << 1 << '\n';
                } else {
                    cout << 0 << '\n';
                }
                break;
            case CMD_TOGGLE:
                S ^= (1 << x);
                break;
            default:
                break;
        }
    }
    return 0;
}
