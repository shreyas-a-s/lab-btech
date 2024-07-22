// CODE GENERATION

#include <stdio.h>
#include <string.h>

char op[2], arg1[5], arg2[5], result[5], in[5][5];

int main() {
  int n, i, j;
  printf("Enter number of three address code: ");
  scanf("%d", &n);

  printf("Enter three address code\n");
  for (i=0; i<n; i++)
    scanf("%s", in[i]);

  j=0;
  for (i=0; i<n; i++) {
    if (in[i][3]=='+') {
      printf("\nMOV R%d, %c", j, in[i][2]);
      printf("\nADD R%d, %c", j, in[i][4]);
      printf("\nMOV %c, R%d", in[i][0], j);
    }
    else if (in[i][3]=='*') {
      printf("\nMOV R%d, %c", j, in[i][2]);
      printf("\nMUL R%d, %c", j, in[i][4]);
      printf("\nMOV %c, R%d", in[i][0], j);
    }
    else if (in[i][3]=='-') {
      printf("\nMOV R%d, %c", j, in[i][2]);
      printf("\nSUB R%d, %c", j, in[i][4]);
      printf("\nMOV %c, R%d", in[i][0], j);
    }
    else if (in[i][3]=='/') {
      printf("\nMOV R%d, %c", j, in[i][2]);
      printf("\nDIV R%d, %c", j, in[i][4]);
      printf("\nMOV %c, R%d", in[i][0], j);
    }
    else if (in[i][1]=='=') {
      printf("\nMOV R%d, %c", j, in[i][2]);
      printf("\nMOV %c, R%d", in[i][0], j);
    }

    j++;
  }

  return 0;
}

/* OUTPUT

Enter number of three address code: 4
Enter three address code
a=b/c
m=x*y
s=a-m
t=s

MOV R0, b
DIV R0, c
MOV a, R0
MOV R1, x
MUL R1, y
MOV m, R1
MOV R2, a
SUB R2, m
MOV s, R2
MOV R3, s
MOV t, R3

*/
