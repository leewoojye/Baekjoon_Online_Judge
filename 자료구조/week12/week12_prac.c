#include <stdio.h>

#define SIZE 10

typedef struct {
  char name[20];
  int id;
  int score;
} Student;

void swap(Student* a, Student* b) {
  Student temp = *a;
  *a = *b;
  *b = temp;
}

void sort_by_id(Student s[], int n) {
  for(int i=0; i<n-1; i++) {
    for(int j=i+1; j<n; j++) {
      if(s[i].id > s[j].id) swap(&s[i], &s[j]);
    }
  }
}

void sort_by_score(Student s[], int n) {
  for(int i=0; i<n-1; i++) {
    for(int j=i+1; j<n; j++) {
      if(s[i].score < s[j].score || (s[i].score == s[j].score && s[i].id > s[j].id)) {
        swap(&s[i], &s[j]);
      }
    }
  }
}

void print_students(Student s[], int n) {
  printf("이름\t학번\t점수\n");
  printf("------------------------\n");
  for(int i=0; i<n; i++) {
    printf("%s\t%d\t%d\n", s[i].name, s[i].id, s[i].score);
  }
}

int main() {
  Student students[SIZE] = {
    {"Kim", 2023005, 85},
    {"Lee", 2023002, 90},
    {"Park", 2023004, 85},
    {"Choi", 2023001, 95},
    {"Jung", 2023003, 90},
    {"Kang", 2023010, 78},
    {"Yoon", 2023007, 88},
    {"Han", 2023006, 95},
    {"Oh", 2023009, 70},
    {"Shin", 2023008, 88}
  };
  Student id_sorted[SIZE], score_sorted[SIZE];

  for(int i=0; i<SIZE; i++) {
    id_sorted[i] = students[i];
    score_sorted[i] = students[i];
  }

  printf("[원본 데이터]\n");
  print_students(students, SIZE);

  printf("\n[학번 기준 오름차순 정렬]\n");
  sort_by_id(id_sorted, SIZE);
  print_students(id_sorted, SIZE);

  printf("\n[점수 기준 내림차순 정렬]\n");
  sort_by_score(score_sorted, SIZE);
  print_students(score_sorted, SIZE);

  return 0;
}
