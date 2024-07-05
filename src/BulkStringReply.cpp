#include "BulkStringReply.h"

BulkStringReply::BulkStringReply(const std::string &msg) {
  m_msg = msg;
  construct();
}

void BulkStringReply::construct() {
	const auto n_chars = std::to_string(m_msg.length());
	m_reply = std::string("$" + n_chars + "\r\n" + m_msg + "\r\n");
}

const std::string BulkStringReply::message() {
  return m_reply;
}
