#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  int p2, p3, n, i, a , j, flag = 0;
  char str[10][10], key[10];
  char temp[10], str1[10][10], str2[10][10];
  int pf1[2], pf2[2];

  pipe(pf1);
  pipe(pf2);

  printf("Enter the number of strings: ");
  scanf("%d", &n);

  for (i=0;i<n;i++) {
    printf("Enter string %d: ", i);
    scanf("%s", str[i]);
  }

  printf("\nThe strings are:\n");
  for (i=0;i<n;i++) {
    printf("%s\n", str[i]);
  }

  write(pf1[1], &n, sizeof(n));
  write(pf1[1], str, sizeof(str));
  close(pf1[1]);

  p2 = fork();
  if (p2 == 0) {
    read(pf1[0], &n, sizeof(n));
    read(pf1[0], str1, sizeof(str1));
    close(pf1[0]);

    for (i=0; i<=n; i++) {
      for (j=i+1; j<=n; j++) {
        if ( (strcmp(str1[i], str1[j])) > 0 ) {
          strcpy(temp, str1[i]);
          strcpy(str1[i], str1[j]);
          strcpy(str1[j], temp);
        }
      }
    }

    printf("\nSorted strings are:\n");
    for (i=0; i<=n; i++) {
      printf("\n%s", str1[i]);
    }

    write(pf2[1], &n, sizeof(n));
    write(pf2[1], str1, sizeof(str1));
    close(pf2[1]);
  } else {
    printf("Enter the key to be searched after sorting: ");
    scanf("%s", key);
    printf("Key to be searched after sorting is: %s", key);

    p3 = fork();
    if (p3 == 0) {
      sleep(5);
      read(pf2[0], &a, sizeof(a));
      read(pf2[0], str2, sizeof(str2));
      close(pf2[0]);

      for (i=0; i<a; i++) {
        if(strcmp(key, str2[i])) {
          flag = 1;
          break;
        }
      }
      if(flag == 0) {
        printf("String is not found!");
      } else {
        printf("\nString is found at index %d", i);
      }
    }
  }
}
