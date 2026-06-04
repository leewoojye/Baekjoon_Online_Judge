#include <stdio.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[20];
    int id;
    int score;
} Student;

// 학생 배열을 다른 배열로 복사한다.
static void copy_students(Student dest[], const Student src[], int n)
{
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// 학생을 학번 오름차순으로 비교한다.
static int compare_id(Student a, Student b)
{
    return a.id - b.id;
}

// 학생을 점수 내림차순, 동점이면 학번 오름차순으로 비교한다.
static int compare_score(Student a, Student b)
{
    if (a.score != b.score) {
        return b.score - a.score;
    }
    return a.id - b.id;
}

// 전달된 비교 함수를 기준으로 학생 배열을 삽입 정렬한다.
static void insertion_sort(Student list[], int n, int (*compare)(Student, Student))
{
    int i;
    int j;

    for (i = 1; i < n; i++) {
        Student key = list[i];

        for (j = i - 1; j >= 0 && compare(list[j], key) > 0; j--) {
            list[j + 1] = list[j];
        }
        list[j + 1] = key;
    }
}

// 학생 배열을 제목과 함께 표 형태로 출력한다.
static void print_students(const char *title, const Student list[], int n)
{
    printf("[%s]\n", title);
    printf("name    id       score\n");
    printf("----------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-7s %d %5d\n", list[i].name, list[i].id, list[i].score);
    }
    printf("\n");
}

// 학생 데이터를 학번순과 점수순으로 정렬해 출력한다.
int main(void)
{
    Student students[] = {
        { "Kim", 2023005, 85 },
        { "Lee", 2023002, 90 },
        { "Park", 2023004, 85 },
        { "Choi", 2023001, 95 },
        { "Jung", 2023003, 90 },
        { "Kang", 2023010, 78 },
        { "Yoon", 2023007, 88 },
        { "Han", 2023006, 95 },
        { "Oh", 2023009, 70 },
        { "Shin", 2023008, 88 }
    };
    int n = (int)(sizeof(students) / sizeof(students[0]));
    Student by_id[MAX_STUDENTS];
    Student by_score[MAX_STUDENTS];

    copy_students(by_id, students, n);
    copy_students(by_score, students, n);

    print_students("original", students, n);

    insertion_sort(by_id, n, compare_id);
    print_students("id ascending", by_id, n);

    insertion_sort(by_score, n, compare_score);
    print_students("score descending", by_score, n);

    return 0;
}
