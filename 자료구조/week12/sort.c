#include <stdio.h>
#define MAX_LENGTH 10
#define swap(a,b,t) ((t)=(a), (a)=(b), (b)=(t)) // swap macro

void insertion_sort(int list[], int len) {
  int i,j, key;
  for(i=1;i<len;i++) {
    key=list[i]; // 덮어쓰기 방지 위한 임시 변수 key 
    for(j=i-1;j>=0 && list[j]>key;j--) {
      list[j+1]=list[j];
    }
    // list[j+1]=list[i];
    list[j+1]=key;
  }
  return;
}

void selection_sort(int list[], int len) {
  int i,j, temp;
  int max_id;
  for(i=0;i<len;i++) {
    max_id=i;
    for(j=i;j<len;j++) { // i는 현재 max 원소를 삽입할 위치, j=i+1 아님
      if(list[j]>list[max_id]) { // 내림차순 선택정렬
        max_id=j;
      }
    }
    swap(list[max_id],list[i],temp);
  }
  return;
}

void bubble_sort(int list[], int len) {
  int i,j,tmp;
  for(i=len-1;i>0;i--) { // 정렬된 부분리스트 i
    for(j=0;j<i;j++) { // 비정렬 부분리스트 j, j+1-j를 비교하므로 j는 i-1까지만 순회
      if(list[j]>list[j+1]) swap(list[j+1],list[j], tmp);
    }
  }
  return;
}

void shell_sort(int list[], int len) {
  return;
}

void merge(int list[], int left, int mid, int right) { // mid
  int list_sorted[MAX_LENGTH];
  int list_idx=0;
  int l_idx=left;
  int r_idx=mid+1;

  while(l_idx<r_idx) { // left<right X
    if(list[l_idx]>=list[r_idx]) list_sorted[list_idx++]=list[r_idx++];
    else list_sorted[list_idx++]=list[l_idx++];
  }

  for(;l_idx<=mid;) list_sorted[list_idx++]=list[l_idx++];
  for(;r_idx<=right;) list_sorted[list_idx++]=list[r_idx++];

  list_idx=0;
  for(int i=left;i<=right;i++) {
    list[i]=list_sorted[list_idx++];
  }
  return;
}

void merge_sort(int list[], int left, int right) { // left, right는 인덱스임
  int mid;
  if(left<right) {
    mid=(left+right)/2;
    merge_sort(list, left, mid);
    merge_sort(list, mid+1, right);
    merge(list, left, mid, right);
  }
  return;
}

void quick_sort(int list[], int len) {
  return;
}

void radix_sort(int list[], int len) {
  return;
}

int main() {
  int list[MAX_LENGTH] = {3,7,32,46};
  // int len = sizeof(list) / sizeof(list[0]);
  int len=4;
  // insertion_sort(list, len);
  // selection_sort(list, len);
  // bubble_sort(list, len);
  merge_sort(list, 0, 3);
  for(int i=0;i<len;i++) {
    printf("%d ", list[i]);
  }
  return 0;
}