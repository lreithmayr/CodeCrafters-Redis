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
#include "Command.h"
#include "BulkStringReply.h"
#include "SimpleStringReply.h"
#include "RedisDB.h"

class Server {
 public:
  Server() = default;

  void init();
  [[noreturn]] void run();
  void process_request(const int fd, const int i);
  void close_connection(const int fd, const int i);
  void process_commands(const int fd, const std::vector<std::string_view> &parsed_request);
  void send_reply(const int fd, RESPReply &reply);

 private:
  int m_sock_fd { -1 };
  int m_client_fd { -1 };
  sockaddr_in m_server_addr;
  sockaddr_in m_client_addr;
  int m_client_addr_len;
  fd_set m_readfds;
  std::vector<int> m_clients;
  std::unordered_map<std::string_view, std::string_view> m_db;
};

#endif //REDIS_STARTER_CPP_INCLUDE_SERVER_H_
