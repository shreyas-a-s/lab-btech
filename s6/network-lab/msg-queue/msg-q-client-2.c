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
} m2;

int main() {
  int msgid;
  m2.type = 2;
  key_t key = ftok("a.c", 'n');
  msgid = msgget(key, 0666 | IPC_CREAT);
  printf("-- Welcome Client 2 --\n");
  do {
    printf(">>> ");
    scanf("%s", m2.str);
    msgsnd(msgid, (void *)&m2, sizeof(m2), 0);
  } while (strcmp(m2.str, "end") != 0);
}
