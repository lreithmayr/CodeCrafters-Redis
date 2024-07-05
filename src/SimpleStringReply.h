#ifndef REDIS_STARTER_CPP_SRC_SIMPLESTRINGREPLY_H_
#define REDIS_STARTER_CPP_SRC_SIMPLESTRINGREPLY_H_

#include "Reply.h"

class SimpleStringReply : public RESPReply {
 public:
  SimpleStringReply(const std::string &msg);
  virtual std::string message() override;

  void construct();

};

#endif //REDIS_STARTER_CPP_SRC_SIMPLESTRINGREPLY_H_
