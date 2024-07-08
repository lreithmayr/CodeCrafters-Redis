#ifndef REDIS_STARTER_CPP_INCLUDE_COMMAND_H_
#define REDIS_STARTER_CPP_INCLUDE_COMMAND_H_

typedef enum {
  ARG_TYPE_STRING,
  ARG_TYPE_INTEGER,
  ARG_TYPE_DOUBLE,
  ARG_TYPE_KEY, /* A string, but represents a keyname */
  ARG_TYPE_PATTERN,
  ARG_TYPE_UNIX_TIME,
  ARG_TYPE_PURE_TOKEN,
  ARG_TYPE_ONEOF, /* Has subargs */
  ARG_TYPE_BLOCK /* Has subargs */
} redisCommandArgType;

typedef struct Command {
  /*
  std::string name;
  redisCommandArgType type;
  std::vector<std::string> args;
  std::vector<std::string> opts;
   */

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
} Command;
#endif //REDIS_STARTER_CPP_INCLUDE_COMMAND_H_
