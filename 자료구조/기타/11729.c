#include <stdio.h>
#include <stdlib.h>

typedef struct data {
  int source;
  int dest;
} data;
int idx=0;
data arr[101]={0,0}; // N=20인 경우 누적 원소가 백만개가 넘게 됨 -> Bus error

void move_plate(int n, int from, int tmp, int to) {
  data data={from,to};
  if(n==1) {
    arr[idx++]=data;
    return;
  }
  move_plate(n-1,from,to,tmp);
  arr[idx++]=data;
  move_plate(n-1,tmp,from,to);
  return;
}

int main() {
  int N;
  scanf("%d",&N);
  move_plate(N,1,2,3);
  printf("%d\n",idx);
  for(int i=0;arr[i].source!=0;i++) {
    printf("%d %d\n",arr[i].source,arr[i].dest);
  }
  return 0;
}