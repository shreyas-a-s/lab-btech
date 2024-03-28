#include <unistd.h>
#include <stdio.h>

int main()
{
  int p2, p3, p4, p5, p6, p7;
  p2 = fork();
  if (p2 == 0)
  {
    p4 = fork();
    if (p4 == 0)
    {
      printf("p4 = %d\n", getpid());
    }
    else
    {
      p5 = fork();
      if (p5 == 0)
      {
        printf("p5 = %d\n", getpid());
      }
      else
      {
        printf("p2 = %d\n", getpid());
      }
    }
  }
  p3 = fork();
  if (p3 == 0)
  {
    p6 = fork();
    if (p6 == 0)
    {
      printf("p6 = %d\n", getpid());
    }
    else
    {
      p7 = fork();
      if (p7 == 0)
      {
        printf("p7 = %d\n", getpid());
      }
      else
      {
        printf("p3 = %d\n", getpid());
      }
    }
  }
  else
  {
    printf("p1 = %d\n", getpid());
  }
}
