#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<char>> matrix;

struct Node {
    pair<int, int> p;
    vector<Node*> children;
};

int makeTree(vector<bool>& alpha, Node* node) { // alpha를 참조로 전달
    int h = 0;
    alpha[matrix[node->p.first][node->p.second] - 'A'] = true;

    // x축으로 -1 이동
    if (node->p.second > 0 && !alpha[matrix[node->p.first][node->p.second - 1] - 'A']) {
        Node* n = new Node;
        n->p = {node->p.first, node->p.second - 1};
        node->children.push_back(n);
        h = max(h, makeTree(alpha, n));
    }
    // x축으로 +1 이동
    if (node->p.second < matrix[0].size() - 1 && !alpha[matrix[node->p.first][node->p.second + 1] - 'A']) {
        Node* n = new Node;
        n->p = {node->p.first, node->p.second + 1};
        node->children.push_back(n);
        h = max(h, makeTree(alpha, n));
    }
    // y축으로 -1 이동
    if (node->p.first > 0 && !alpha[matrix[node->p.first - 1][node->p.second] - 'A']) {
        Node* n = new Node;
        n->p = {node->p.first - 1, node->p.second};
        node->children.push_back(n);
        h = max(h, makeTree(alpha, n));
    }
    // y축으로 +1 이동
    if (node->p.first < matrix.size() - 1 && !alpha[matrix[node->p.first + 1][node->p.second] - 'A']) {
        Node* n = new Node;
        n->p = {node->p.first + 1, node->p.second};
        node->children.push_back(n);
        h = max(h, makeTree(alpha, n));
    }

    alpha[matrix[node->p.first][node->p.second] - 'A'] = false; // 방문 기록 복구
    return h + 1; // 현재 노드 높이를 포함
}

void deleteTree(Node* root) {
    for (Node* child : root->children) {
        deleteTree(child);
    }
    delete root;
}

int main() {
    fastio;
    int R, C;
    string s;
    cin >> R >> C;
    matrix.resize(R, vector<char>(C));
    for (int i = 0; i < R; ++i) {
        cin >> s;
        for (int j = 0; j < C; ++j) {
            matrix[i][j] = s[j];
        }
    }
    vector<bool> alpha(26, false);
    Node* n = new Node;
    n->p = {0, 0};
    int height = makeTree(alpha, n);
    cout << height;

    // 트리 메모리 해제
    deleteTree(n);

    return 0;
}
