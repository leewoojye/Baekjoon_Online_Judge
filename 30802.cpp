#include <iostream>
#include <vector>
#include <cmath> // ceil 함수 사용을 위해 포함

int main() {
    // 입출력 속도 향상
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long N; // 참가자의 수
    std::cin >> N;

    std::vector<long long> shirt_counts(6); // 6가지 티셔츠 사이즈별 신청자 수
    for (int i = 0; i < 6; ++i) {
        std::cin >> shirt_counts[i];
    }

    long long T, P; // 티셔츠 묶음 단위 T, 펜 묶음 단위 P
    std::cin >> T >> P;

    // 티셔츠 묶음 수 계산
    long long total_shirt_bundles = 0;
    for (int i = 0; i < 6; ++i) {
        // 각 사이즈별 필요한 티셔츠 묶음 수 계산 (올림)
        // (신청자 수 + 묶음 단위 - 1) / 묶음 단위 를 통해 올림 연산을 수행합니다.
        // 또는 ceil 함수 사용: total_shirt_bundles += static_cast<long long>(std::ceil(static_cast<double>(shirt_counts[i]) / T));
        total_shirt_bundles += (shirt_counts[i] + T - 1) / T;
    }

    // 펜 묶음 수와 낱개 수 계산
    long long pen_bundles = N / P; // 펜 P자루씩 최대 몇 묶음
    long long single_pens = N % P; // 펜 낱개 몇 개

    // 결과 출력
    std::cout << total_shirt_bundles << std::endl;
    std::cout << pen_bundles << " " << single_pens << std::endl;

    return 0;
}