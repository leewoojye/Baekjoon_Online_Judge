#include <stdio.h>
#include <time.h>
#include "../week05/queue.h"
#define MAX_LENGTH 10
# define BUCKETS 10
#define DIGITS 2
#define swap(a,b,t) ((t)=(a), (a)=(b), (b)=(t)) // swap macro

// void print_list(int list[], int len) {
//   for(int i=0;i<len;i++) printf("%d ",list[i]);
//   printf("\n");
// }

void merge(int list[], int left, int mid, int right) {
  int list_sorted[MAX_LENGTH]; // 덮어쓰기 방지
  int l=left;
  int r=mid+1; // int r=right; // 부분 리스트는 정렬된 상태이므로 left와 mid+1 인덱스 원소끼리 비교해야함
  int idx=0;
  while(l<=mid && r<=right) {
    if(list[l]<=list[r]) list_sorted[idx++]=list[l++];
    else list_sorted[idx++]=list[r++];
  }
  for(;l<=mid;) list_sorted[idx++]=list[l++];
  for(;r<=right;) list_sorted[idx++]=list[r++];
  for(int i=left,j=0;i<=right;i++,j++) list[i]=list_sorted[j];
}

void merge_sort(int list[], int left, int right) {
  if(left<right) {
    int mid=(left+right)/2;
    merge_sort(list,left,mid);
    merge_sort(list,mid+1,right); // mid+1
    merge(list,left,mid,right); // mid
  }
}

int main() {
  srand(time(NULL));

  int list[MAX_LENGTH];
  // int len = sizeof(list) / sizeof(list[0]);
  // int len=10;

  for(int i=0;i<MAX_LENGTH;i++) {
    list[i]=rand()%100+1;
  }

  // insertion_sort(list, len);
  // selection_sort(list, len);
  // bubble_sort(list, len);
  merge_sort(list, 0, 9); // left, right는 인덱스임
  // quick_sort(list, 0, 3);
  // radix_sort(list, len);
  // shell_sort(list, len);

  for(int i=0;i<MAX_LENGTH;i++) {
    printf("%d ", list[i]);
  }
  return 0;
}