#include <stdio.h>
#include <time.h>
#include "../week05/queue.h"
#define MAX_LENGTH 10
# define BUCKETS 10
#define DIGITS 2
#define swap(a,b,t) ((t)=(a), (a)=(b), (b)=(t)) // swap macro

void print_list(int list[], int len) {
  for(int i=0;i<len;i++) printf("%d ",list[i]);
  printf("\n");
}

// 삽입 정렬
void insertion_sort(int list[], int len) {
  int i,j, key;
  for(i=1;i<len;i++) { // 총 원소수-1만큼만 반복해도 정렬가능
    key=list[i]; // 덮어쓰기 방지 위한 임시 변수 key 
    for(j=i-1;j>=0 && list[j]>key;j--) {
      list[j+1]=list[j];
    }
    // list[j+1]=list[i];
    list[j+1]=key;
  }
  return;
}

// 선택 정렬
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

// 단일 부분리스트에 대해 삽입정렬
void shell_selection_sort(int list[], int start, int len, int gap) {
  int i,j,key;
  int tmp;
  for(i=start;i+gap<len;i+=gap) {
    for(j=i+gap;j>=start;j-=gap) {
      if(list[j-gap]>list[j]) swap(list[j-gap],list[j],tmp); // 반복마다 swap을 하면 교재예제보다 이동비용이 많이듦, 교안에서는 우측이동만 수행하다 마지막에 삽입원소를 한번 대입함 (아래 참고)
    }
  }
}

// 단일 부분리스트 삽입 정렬
void shell_selection_sort_better(int list[], int start, int len, int gap) {
  int j,key;
  for(int i=start+gap;i<len;i+=gap) { // 시작위치를 현재 삽입할 노드 기준으로 해야, start는 첫 노드인데 삽입정렬은 두번째 노드부터 삽입대상으로 정함
    key=list[i]; // 덮어쓰기 방지 위해 삽입노드 key 임시로 저장

    // i가 삽입노드를 가리키므로 삽입비교대상노드는 i보다 gap만큼 작아야 함
    for(j=i-gap;j>=start&&list[j]>key;j-=gap) { // j는 삽입노드와 비교할 노드를 가리켜야
      list[j+gap]=list[j];
    }
    list[j+gap]=key;
  }
}

void shell_sort(int list[], int len) {
  int gap=len/2;
  if(gap%2==0) gap++;
  for (;gap>1;) {
    for(int i=0;i+gap<len;i++) { // 부분리스트 개수만큼 반복
      // shell_selection_sort(list,i,len,gap);
      shell_selection_sort_better(list,i,len,gap);
    }
    gap /= 2;
    if(gap%2==0) gap++;
  }
  insertion_sort(list, len); // gap=1 삽입정렬
  return;
}

void merge(int list[], int left, int mid, int right) { // mid
  int list_sorted[MAX_LENGTH];
  int list_idx=0;
  int l_idx=left;
  int r_idx=mid+1;

  // l_idx <= mid && r_idx <= right 가 정확한 표현 !!
  while(l_idx <= mid && r_idx <= right) { // left<right, l_idx<r_idx X
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

int partition(int list[], int left, int right) { // pivot으로 부분리스트 이진 분할
  int pivot=left;
  int l_idx=left+1;
  int r_idx=right;
  int tmp;

  while(l_idx<r_idx) {
    while(list[l_idx]<pivot && l_idx<r_idx) l_idx++;
    while(list[r_idx]>=pivot && l_idx<r_idx) r_idx--;
    if(l_idx<r_idx) swap(list[l_idx], list[r_idx], tmp);
  }
  swap(list[pivot], list[l_idx], tmp);
  return l_idx;
}

void quick_sort(int list[], int left, int right) {
  int pivot;
  if(left<right) {
    pivot=partition(list, left, right);
    quick_sort(list, left, pivot-1);
    quick_sort(list, pivot+1, right);
  }
  return;
}

void radix_sort(int list[], int len) {
  QueueType q;
  init_queue(&q);

  int bucket_id;
  QueueType buckets[BUCKETS];
  for (int j = 0; j < BUCKETS; j++) {
      init_queue(&buckets[j]);
  }

  for(int i=1, d=1;d<=DIGITS;i*=10, d++) { // factor i
    for(int j=0;j<len;j++) {
      bucket_id=(list[j]/i)%10;
      enqueue(&buckets[bucket_id], list[j]);
    }
    for(int j=0, idx=0;j<BUCKETS;j++) {
      while(!is_empty(&buckets[j])) list[idx++]=dequeue(&buckets[j]);
    }
  }
  // for(int i=0, idx=0;i<BUCKETS;i++) {
  //   while(!is_empty(&buckets[i])) list[idx++]=dequeue(&buckets[i]);
  // }
  return;
}

int main() {
  srand(time(NULL));
  int list[MAX_LENGTH];
  // int len = sizeof(list) / sizeof(list[0]);
  int len=10;
  for(int i=0;i<len;i++) {
    list[i]=rand()%100+1;
  }

  // insertion_sort(list, len);
  // selection_sort(list, len);
  // bubble_sort(list, len);
  // merge_sort(list, 0, 3); // left, right는 인덱스임
  // quick_sort(list, 0, 3);
  // radix_sort(list, len);
  shell_sort(list, len);
  for(int i=0;i<len;i++) {
    printf("%d ", list[i]);
  }
  return 0;
}