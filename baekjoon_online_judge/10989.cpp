#include <cstdio>

int main() {
    int N;
    scanf("%d", &N);

    const int MAX = 10000;
    int count[MAX + 1] = {0};

    int num;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &num);
        ++count[num];
    }

    for (int i = 1; i <= MAX; ++i) {
        while (count[i]--) {
            printf("%d\n", i);
        }
    }
    return 0;
}