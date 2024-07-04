#ifndef REDIS_STARTER_CPP_SRC_PROTOCOL_H_
#define REDIS_STARTER_CPP_SRC_PROTOCOL_H_

#include <string>
#include <array>
#include <iostream>
#include <exception>
#include <sstream>
#include <stdio.h>
#include "stringzilla/stringzilla.hpp"

#include "Utils.h"
#include "Command.h"

namespace sz = ashvardanian::stringzilla;

typedef struct ByteType {
  static const char ASTERISK_BYTE = '*';
  static const char DOLLAR_BYTE = '$';
  static const char PLUS_BYTE = '+';
  static const char MINUS_BYTE = '-';
  static const char COLON_BYTE = ':';
} ByteType;

class Protocol {
 public:
  static inline sz::string parse(sz::string_view &rcvd_msg) {
	const char first_byte = rcvd_msg.at(0);
	std::cout << "first byte: " << first_byte << '\n';
	switch (first_byte) {
	  case ByteType::ASTERISK_BYTE:
		return parse_array(rcvd_msg);
	  case ByteType::DOLLAR_BYTE:
		return parse_bulk_string(rcvd_msg);
	  case ByteType::PLUS_BYTE:
		return parse_simple_string(rcvd_msg);
	  default:
		throw std::runtime_error("Invalid command!");
	}
  };

  static inline sz::string parse_array(sz::string_view &msg) {
	sz::string ret;
	sz::string_view msg_sz(msg);
	msg_sz.remove_prefix(1);
	// auto len = msg_sz.front(1);
	sz::string_view rest = msg_sz.sub(1, -1).lstrip(sz::char_set("\r\n"));
	ret.append(parse(rest));
	return ret;
  };

  static inline sz::string parse_bulk_string(sz::string_view &msg) {
	auto split = msg.split(sz::char_set("\r\n")).template to<std::vector<sz::string>>();
	auto cmd = split.at(2);
	if (cmd == "ECHO") {
	  return build_response(cmd::echo(split.at(6)));
	}
	if (cmd == "PING") {
	  return build_response(cmd::ping());
	}
	throw std::runtime_error("Command couldn't be parsed!");
  };

  static sz::string parse_simple_string(sz::string_view &rcvd_msg) {
	return ashvardanian::stringzilla::string();
  };

  static inline sz::string build_response(const sz::string_view &body) {
	const auto n_chars = std::to_string(body.length());
	auto ret = sz::string("$" + n_chars +"\r\n" + body.data() + "\r\n");
	return ret;
  };
};

#endif //REDIS_STARTER_CPP_SRC_PROTOCOL_H_
