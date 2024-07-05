#ifndef REDIS_STARTER_CPP_INCLUDE_COMMAND_H_
#define REDIS_STARTER_CPP_INCLUDE_COMMAND_H_

#include "Server.h"

class Command {
 public:
  static inline std::string ECHO(const std::string_view &msg) {
	return std::string(msg);
  }

  static inline std::string PING() {
	return std::string("PONG");
  }

  template<typename K, typename V>
  static inline std::string SET(const K &key, const V &value) {
	std::cout << "Key: " << key << " Value: " << value << "\n";
	return std::string("OK");
  }

  template<typename V>
  static inline std::string GET(const V &value) {
	return std::string(value);
  }
};
#endif //REDIS_STARTER_CPP_INCLUDE_COMMAND_H_
