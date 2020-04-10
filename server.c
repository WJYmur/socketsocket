/****************** SERVER CODE ****************/
/*****https://www.programminglogic.com/example-of-client-server-program-in-c-using-sockets-and-tcp/*****/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
  int s, newSocket, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  s = socket(PF_INET, SOCK_STREAM, 0);

  portNum = 7890;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

  bind(s, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  if (listen(s, 5) == 0)
    printf("Listening\n");
  else
    printf("Error\n");

  addr_size = sizeof(serverStorage);

  while (1)
  {
    newSocket = accept(s, (struct sockaddr *)&serverStorage, &addr_size);

    nBytes = 1;
    while (nBytes != 0)
    {
      nBytes = recv(newSocket, buffer, 1024, 0);
      printf("Get Data : %s", buffer);
      send(newSocket, buffer, nBytes, 0);
    }
    close(newSocket);
  }

  close(s);
  return 0;
}
