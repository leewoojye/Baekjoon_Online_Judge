#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef int element;
typedef struct list {
  element data[MAX_SIZE];
  int size;
} list;

void init_list(list *l) {
  l->size=0;
}

int is_empty(list *l) {
  return l->size==0;
}

int is_full(list *l) {
  return l->size==MAX_SIZE;
}

void insert(list *l, int pos, element e) {
  if(is_full(l) || l->size<pos) return; // insert_last() 기능 포함된 조건문
  int prev=l->data[pos];
  int tmp;
  for(int i=pos+1;i<l->size;i++) { // 기존 데이터 우측으로 한칸씩 옮기기
    tmp=l->data[i];
    l->data[i]=prev;
    prev=tmp;
  }
  l->data[pos]=e;
  l->size++;
  return;
}

void insert_last(list *l, element e) {
  if(is_full(l)) return;
  l->data[(l->size)++]=e;
  return;
}

element delete(list *l) {
  if(is_empty(l)) return 0;
  return l->data[--(l->size)];
}

void print_list(list *l) {
  if(is_empty(l)) return;
  for(int i=0;i<l->size;i++) {
    printf("%d->",l->data[i]);
  }
  printf("\n");
  return;
}

int main() {
  list l;
  init_list(&l);
  insert(&l,0,1);
  insert(&l,1,2);
  print_list(&l);
  return 0;
}