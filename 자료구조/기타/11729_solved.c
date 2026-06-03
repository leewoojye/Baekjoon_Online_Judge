#include <stdio.h>
#include <math.h>

void move_plate(int n, int from, int tmp, int to) {
  if(n==1) {
    printf("%d %d\n", from, to);
    return;
  }
  move_plate(n-1, from, to, tmp);
  printf("%d %d\n", from, to);
  move_plate(n-1, tmp, from, to);
  return;
}

int main() {
  int N;
  scanf("%d",&N);
  long long count = (long long)pow(2, N) - 1;
  printf("%lld\n", count);
  if (N <= 20) {
      move_plate(N, 1, 2, 3);
  }
  return 0;
}
