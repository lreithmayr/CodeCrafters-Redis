#ifndef REDIS_STARTER_CPP_SRC_BULKSTRINGREPLY_H_
#define REDIS_STARTER_CPP_SRC_BULKSTRINGREPLY_H_

#include "Reply.h"

class BulkStringReply : public RESPReply {
 public:
  BulkStringReply(const std::string &msg);
  virtual std::string message() override;

  void construct();

};

#endif //REDIS_STARTER_CPP_SRC_BULKSTRINGREPLY_H_
