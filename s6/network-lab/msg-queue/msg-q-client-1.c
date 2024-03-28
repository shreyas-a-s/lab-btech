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
} m1;

int main() {
  int msgid;
  m1.type = 1;
  key_t key = ftok("a.c", 'n');
  msgid = msgget(key, 0666 | IPC_CREAT);
  printf("-- Welcome Client 1 --\n");
  do {
    printf(">>> ");
    scanf("%s", m1.str);
    msgsnd(msgid, (void *)&m1, sizeof(m1), 0);
  } while (strcmp(m1.str, "end") != 0);
}
