#ifndef REDIS_STARTER_CPP_INCLUDE_COMMAND_H_
#define REDIS_STARTER_CPP_INCLUDE_COMMAND_H_

#include "stringzilla/stringzilla.hpp"

namespace sz = ashvardanian::stringzilla;

namespace cmd {
inline sz::string echo(const sz::string_view &msg) {
  return sz::string(msg);
}

inline sz::string ping() {
  return sz::string("PONG");
}
} // namespace cmd


#endif //REDIS_STARTER_CPP_INCLUDE_COMMAND_H_
