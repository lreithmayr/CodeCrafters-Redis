#include "SimpleStringReply.h"
SimpleStringReply::SimpleStringReply(const std::string &msg) {
  m_msg = msg;
  construct();
}
const std::string SimpleStringReply::message() {
  return m_reply;
}

void SimpleStringReply::construct() {
  m_reply = std::string("+" + m_msg + "\r\n");
}
