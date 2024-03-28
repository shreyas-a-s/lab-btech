#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  struct sockaddr_in caddr;
  int rec, cid;
  unsigned int port;
  char buf[32], tmp[32];
  int i, j, k, c, l, s, snd;
  printf("Enter the port number\n");
  scanf("%d", &port);

  cid = socket(AF_INET, SOCK_STREAM, 0);
  if (cid == -1) {
    perror("Socket creation failed\t");
    return 0;
  }

  memset(&caddr, 0, sizeof(caddr));
  caddr.sin_family = AF_INET;
  caddr.sin_port = htons(port);
  caddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  s = connect(cid, (struct sockaddr *)&caddr, sizeof(caddr));
  if (s < 0) {
    perror("Connection failed\n");
    return 0;
  }
  do {
    printf("\nEnter the string\n");
    scanf("%s", tmp);
    snd = send(cid, tmp, sizeof(tmp), 0);
    if (snd < 0) {
      perror("Send failed\n");
    }
    if (strcmp(tmp, "quit") == 0) {
      printf("\n client sign-out\n");
      return 0;
    }
    printf("\nData send to server by keyboard\n");
    strncpy(buf, "", 32);
    rec = recv(cid, buf, sizeof(buf), 0);
    if (rec < 0) {
      printf("\nrec = %d\n", rec);
      perror("\nReceive failed\n");
      return 0;
    }
    printf("\nFrom server;\t%s", buf);
  } while (1);

  shutdown(cid, 1);
  close(cid);
}
