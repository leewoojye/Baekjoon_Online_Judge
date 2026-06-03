#include <stdio.h>
#include <string.h>

int main() {
    char str1[100];
    char str2[100];

    // -----------------------------
    // 1. scanf 입력 (공백 전까지만)
    // -----------------------------
    printf("scanf 입력 (공백 X): ");
    scanf("%99s", str1);
    printf("입력 결과: %s\n\n", str1);

    // 입력 버퍼 비우기 (중요!)
    getchar();

    // -----------------------------
    // 2. fgets 입력 (공백 포함)
    // -----------------------------
    printf("fgets 입력 (공백 O): ");
    fgets(str2, sizeof(str2), stdin);

    // 개행 제거
    str2[strcspn(str2, "\n")] = '\0';

    printf("입력 결과: %s\n\n", str2);

    // -----------------------------
    // 3. 문자열 길이 (strlen)
    // -----------------------------
    printf("str2 길이: %lu\n\n", strlen(str2));

    // -----------------------------
    // 4. 문자열 복사 (strcpy)
    // -----------------------------
    char copy[100];
    strcpy(copy, str2);
    printf("복사 결과: %s\n\n", copy);

    // -----------------------------
    // 5. 문자열 비교 (strcmp)
    // -----------------------------
    if (strcmp(str1, str2) == 0) {
        printf("두 문자열은 같습니다\n\n");
    } else {
        printf("두 문자열은 다릅니다\n\n");
    }

    // -----------------------------
    // 6. 문자열 연결 (strcat)
    // -----------------------------
    char combined[200] = "";
    strcat(combined, str1);
    strcat(combined, " ");
    strcat(combined, str2);

    printf("연결 결과: %s\n\n", combined);

    // -----------------------------
    // 7. 문자 하나씩 출력
    // -----------------------------
    printf("문자 하나씩 출력: ");
    for (int i = 0; str2[i] != '\0'; i++) {
        printf("%c ", str2[i]);
    }
    printf("\n\n");

    // -----------------------------
    // 8. 직접 strlen 구현 테스트
    // -----------------------------
    int len = 0;
    while (str2[len] != '\0') {
        len++;
    }
    printf("직접 구현 strlen: %d\n", len);

    return 0;
}