#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 100

struct message {
  int type;
  char str[MAX_MESSAGE_SIZE];
} m;

int main() {
  char buff[MAX_MESSAGE_SIZE];
  int msgid, i, count, c = 0;
  key_t key = ftok("a.c", 'n');
  msgid = msgget(key, 0666 | IPC_CREAT);
  y:msgrcv(msgid, (void *)&m, sizeof(m), 0, 0);

  if (strcmp(m.str, "end") == 0) {
    goto x;
  }

  strcpy(buff, m.str);

  if (m.type == 1) {
    printf("\nClient1: %s\n", buff);
    printf("Reverse of string: ");
    for (i = strlen(buff); i >= 0; i--) {
      printf("%c", buff[i]);
    }
    printf("\n");
  } else if (m.type == 2) {
    printf("\nClient2: %s", buff);
    count = 0;
    for (i = 0; i < strlen(buff); i++) {
      switch (buff[i]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        count++;
        break;
      }
    }
    printf("Number of vowels in string = %d\n", count);
  }
  goto y;
x:
  printf("\nMessages are received\n");
}
