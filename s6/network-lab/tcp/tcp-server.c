#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  struct sockaddr_in saddr, caddr;
  int sid, acp;
  unsigned int n, port;
  char buf[32], tmp[32];
  int i, j, k, c, l, p;
  printf("Enter the port number\n");
  scanf("%d", &port);

  sid = socket(AF_INET, SOCK_STREAM, 0);
  if (sid == -1) {
    perror("Socket creation failed\t");
    return 0;
  }

  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (bind(sid, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
    perror("bind failed\n");
    return 0;
  }
  printf("\nServer started...Waiting for client to connect...");

  if (listen(sid, 10) < 0) {
    perror("\nListen failed\n");
    return 0;
  }

  n = sizeof(caddr);
  acp = (accept(sid, (struct sockaddr *)&caddr, &n));
  if (acp < 0) {
    perror("\nAccept failed\n");
    return 0;
  }

  do {
    memset(tmp, 0, sizeof(tmp));
    l = recv(acp, tmp, sizeof(tmp), 0);
    if (l < 0) {
      perror("\nReceive failed\n");
      return 0;
    }
    printf("\nReceive success\ndata from client = %s\n", tmp);
    if (strcmp(tmp, "quit") == 0) {
      printf("\nServer Sign-out...\n");
      return 0;
    }
    memset(buf, 0, sizeof(buf));
    printf("Enter the data to client\n");
    scanf("%s", buf);
    l = send(acp, buf, sizeof(buf), 0);
    if (l < 0) {
      perror("\nSending failed\n");
      return 0;
    }
    printf("Data has been sent to client\n");
  } while (1);

  shutdown(sid, 2);
  close(acp);
  close(sid);
}
