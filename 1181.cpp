#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<string> list(N);  // N을 입력받은 후 벡터 크기 설정
    for (int i = 0; i < N; ++i) {
        cin >> list[i];
    }

    vector<vector<string>> matrix(51);  // 0~50 길이의 문자열을 저장할 2차원 벡터

    for (int i = 0; i < N; ++i) {
        matrix[list[i].length()].push_back(list[i]);
    }

    for (int i = 1; i < 51; ++i) {
        if (matrix[i].size() > 1) {
            sort(matrix[i].begin(), matrix[i].end());
            auto last = unique(matrix[i].begin(), matrix[i].end());
            matrix[i].erase(last, matrix[i].end());  // 중복된 원소를 제거한 후 벡터 크기 조정// 한 번만 정렬
        }
    }

    for (int i = 1; i < 51; ++i) {
        if (matrix[i].size() == 0) {
            continue;
        }
        for (int j = 0; j < matrix[i].size(); ++j) {  // j로 수정
            cout << matrix[i][j] << endl;
        }
    }

    return 0;
}