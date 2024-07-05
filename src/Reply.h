#ifndef REDIS_STARTER_CPP_INCLUDE_REPLY_H_
#define REDIS_STARTER_CPP_INCLUDE_REPLY_H_

#include <string>

class RESPReply {
 public:
  RESPReply() = default;
  ~RESPReply() = default;

  virtual std::string message() = 0;

 protected:
  std::string m_msg;
  std::string m_reply;
};

#endif //REDIS_STARTER_CPP_INCLUDE_REPLY_H_
