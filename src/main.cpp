#include "Server.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  Server server;
  server.init();
  server.run();
  return 0;
}
