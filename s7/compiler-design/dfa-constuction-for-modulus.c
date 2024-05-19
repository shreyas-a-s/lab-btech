#include <stdio.h>
#include <string.h>

int main() {
  int tr[5][2];
  char str[20];
  int flag = 0, i, j, n, l, p;
  printf("Enter modulos: ");
  scanf("%d", &n);

  printf("States of modulos %d = { ", n);
  for (i=0; i<n; i++) {
    printf("q%d, ", i);
  }
  printf("\b\b }\n");
  printf("Final state = q0\n\n");

  for(i=0; i<n; i++) {
    p = 2*i + 0;
    tr[i][0] = p%n;
    p = 2*i + 1;
    tr[i][1] = p%n;
  }

  printf("\t0\t1\n");
  for (i=0; i<n; i++) {
    printf("q%d\t", i);
    for (j=0; j<2; j++) {
      printf("%d\t", tr[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  printf("Enter the string: ");
  scanf("%s", str);

  int s = 0;
  for (i=0; i<strlen(str); i++) {
    j = str[i] - '0';
    s = tr[s][j];
    printf("(q%d,%d)=q%d\n", i, j, s);
  }

  if (s == 0) {
    printf("q%d is final state hence accepted\n", s);
  }
  else {
    printf("q%d is not final state hence rejected\n", s);
  }
  return 0;
}
