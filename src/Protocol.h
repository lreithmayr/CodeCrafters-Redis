#ifndef REDIS_STARTER_CPP_SRC_PROTOCOL_H_
#define REDIS_STARTER_CPP_SRC_PROTOCOL_H_

#include <string>
#include <array>
#include <iostream>
#include <exception>
#include <sstream>
#include <stdio.h>
#include <memory>

#include "Utils.h"
#include "Command.h"
#include "BulkStringReply.h"

typedef struct ByteType {
  static const char ASTERISK_BYTE = '*';
  static const char DOLLAR_BYTE = '$';
  static const char PLUS_BYTE = '+';
  static const char MINUS_BYTE = '-';
  static const char COLON_BYTE = ':';
} ByteType;

class Protocol {
 public:
  static inline std::shared_ptr<RESPReply> parse(std::string_view &rcvd_msg) {
	const char first_byte = rcvd_msg.at(0);
	switch (first_byte) {
	  case ByteType::ASTERISK_BYTE:
		return parse_array(rcvd_msg);
	  case ByteType::DOLLAR_BYTE:
		return parse_bulk_string(rcvd_msg);
	//   case ByteType::PLUS_BYTE:
	// 	return parse_simple_string(rcvd_msg);
	  default:
		throw std::runtime_error("Invalid command!");
	}
  };

  static inline std::shared_ptr<RESPReply> parse_array(std::string_view &msg) {
	auto msg_stripped = strutils::split_at(msg, 0).at(1);
	auto rest = strutils::split_first_CRLF(msg_stripped, 0).at(1);
	return parse(rest);
  };

  static inline std::shared_ptr<RESPReply> parse_bulk_string(std::string_view &msg) {
	auto split = strutils::split_CRLF(msg);
	auto cmd = split.at(1);
	if (cmd == "ECHO") {
	  return std::make_shared<BulkStringReply>(Command::ECHO(split.at(6)));
	}
	if (cmd == "PING") {
	  return std::make_shared<BulkStringReply>(Command::PING());
	}
	if (cmd == "SET") {
	  auto key = split.at(3);
	  auto val = split.at(5);
	  return std::make_shared<BulkStringReply>(Command::SET(key, val));
	}
	if (cmd == "GET") {
	  auto key = split.at(3);
	  auto val = split.at(5);
	  return std::make_shared<BulkStringReply>(Command::SET(key, val));
	}
	throw std::runtime_error("Command couldn't be parsed!");
  };
};

#endif //REDIS_STARTER_CPP_SRC_PROTOCOL_H_
