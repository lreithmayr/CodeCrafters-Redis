#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUF_SIZE 256

void error(const char *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char **argv) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
	error("Failed to create server socket\n");
  }

  // Since the tester restarts your program quite often, setting SO_REUSEADDR
  // ensures that we don't run into 'Address already in use' errors
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
	error("setsockopt failed\n");
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(6379);

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
	error("Failed to bind to port 6379\n");
  }

  int connection_backlog = 5;
  if (listen(server_fd, connection_backlog) != 0) {
	error("listen failed\n");
  }

  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);

  std::cout << "Waiting for a client to connect...\n";

  int acc_sockfd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
  if (acc_sockfd < 0) {
	error("Error on accept\n");
  }
  std::cout << "Client connected\n";

  char rbuf[BUF_SIZE];
  while(read(acc_sockfd, rbuf, sizeof(rbuf) - 1)) {
	const char wbuf[] = "+PONG\r\n";
	int n = write(acc_sockfd, wbuf, sizeof(wbuf) - 1);
	if (n < 0) {
	  error("ERROR writing to socket");
	}
  }

  close(acc_sockfd);
  close(server_fd);

  return 0;
}
