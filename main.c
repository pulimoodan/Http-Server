#include "Server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void launch(struct Server *server) {
  char buffer[30000];
  char *hello =
      "HTTP/1.1 200 OK\r\nDate: Fri, 01 Nov 2024 12:58:53 GMT\r\nServer: "
      "Apache/2.2.14 (Win32)\r\nLast-Modified: Thu, 31 Oct 2024 "
      "19:15:56 GMT\r\nContent-Length: 41\r\nContent-Type: "
      "text/html\r\nConnection: "
      "close\r\n\r\n<html><body><h1>Hello!</h1></body></html>";
  printf("%s\n", hello);
  int address_length = sizeof(server->address);
  int new_socket;

  while (1) {
    printf("===== WAITING FOR CONNECTION =====\n");
    new_socket = accept(server->socket, (struct sockaddr *)&server->address,
                        (socklen_t *)&address_length);
    read(new_socket, buffer, 30000);
    printf("%s\n", buffer);

    write(new_socket, hello, strlen(hello));
    close(new_socket);
  }
}

int main() {
  struct Server server =
      server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
  server.launch(&server);

  return 0;
}
