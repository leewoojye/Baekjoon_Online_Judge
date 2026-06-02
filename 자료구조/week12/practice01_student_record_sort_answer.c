#include <stdio.h>
#include <string.h>

#define SIZE 10

typedef struct {
    char name[20];
    int id;
    int score;
} Student;

static void print_students(const char *title, const Student students[], int n)
{
    printf("%s\n", title);
    printf("Name    ID       Score\n");
    printf("----------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-7s %d %5d\n", students[i].name, students[i].id, students[i].score);
    }
    printf("\n");
}

static int compare_by_id_asc(Student a, Student b)
{
    return a.id - b.id;
}

static int compare_by_score_desc_id_asc(Student a, Student b)
{
    if (a.score != b.score) {
        return b.score - a.score;
    }
    return a.id - b.id;
}

static void insertion_sort(Student students[], int n,
                           int (*compare)(Student, Student))
{
    for (int i = 1; i < n; i++) {
        Student key = students[i];
        int j = i - 1;

        while (j >= 0 && compare(students[j], key) > 0) {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
}

static void copy_students(Student dest[], const Student src[], int n)
{
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main(void)
{
    Student original[SIZE] = {
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
    Student by_id[SIZE];
    Student by_score[SIZE];

    copy_students(by_id, original, SIZE);
    copy_students(by_score, original, SIZE);

    print_students("[Original Data]", original, SIZE);

    insertion_sort(by_id, SIZE, compare_by_id_asc);
    print_students("[Sorted by ID ascending]", by_id, SIZE);

    insertion_sort(by_score, SIZE, compare_by_score_desc_id_asc);
    print_students("[Sorted by score descending, ID ascending on tie]", by_score, SIZE);

    return 0;
}
