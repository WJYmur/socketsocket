/****************** CLIENT CODE ****************/
/*****https://www.programminglogic.com/example-of-client-server-program-in-c-using-sockets-and-tcp/*****/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int s, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  portNum = 7890;

  s = socket(PF_INET, SOCK_STREAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

  addr_size = sizeof(serverAddr);
  connect(s, (struct sockaddr *)&serverAddr, addr_size);

  while (1)
  {
    printf("\nType a sentence to send to server:\n");
    
    fgets(buffer, 1024, stdin);
    printf("You typed: %s\n", buffer);

    nBytes = strlen(buffer) + 1;

    send(s, buffer, nBytes, 0);
    recv(s, buffer, 1024, 0);

    printf("Data received: %s", buffer);
  }
  close(s);
  return 0;
}
