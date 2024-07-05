#ifndef REDIS_STARTER_CPP_INCLUDE_SERVER_H_
#define REDIS_STARTER_CPP_INCLUDE_SERVER_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>
#include <sys/fcntl.h>
#include <sys/select.h>

#include "Protocol.h"

class RedisDB;

class Server {
 public:
  Server() = default;

  void init();
  [[noreturn]] void run();
  void process_command(const int &fd, const int i);
  void close_connection(const int &fd, const int i);

  static std::shared_ptr<RedisDB> database() {
	return m_db;
  }

 private:
  int m_sock_fd { -1 };
  int m_client_fd { -1 };
  sockaddr_in m_server_addr;
  sockaddr_in m_client_addr;
  int m_client_addr_len;
  fd_set m_readfds;
  std::vector<int> m_clients;
  static std::shared_ptr<RedisDB> m_db;
};

#endif //REDIS_STARTER_CPP_INCLUDE_SERVER_H_
