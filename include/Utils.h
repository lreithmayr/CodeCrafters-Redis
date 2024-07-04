#ifndef REDIS_STARTER_CPP_INCLUDE_UTILS_H_
#define REDIS_STARTER_CPP_INCLUDE_UTILS_H_

#include <vector>
#include <string>

namespace strutils {
template<typename T>
static std::vector<std::string> split(T &str, const std::string &del) {
  std::vector<std::string> elements;
  std::string::size_type pos = 0;
  std::string::size_type prev = 0;
  while ((pos = str.find(del, prev)) != std::string::npos) {
	elements.emplace_back(str.substr(prev, pos - prev));
	prev = pos + 1;
  }
  return elements;
}

template<typename T>
static std::vector<std::string> split_at(T &str, const int pos) {
  std::vector<std::string> elements;
  elements.emplace_back(str.substr(0, pos));
  elements.emplace_back(str.substr(pos, str.length() - pos));
  return elements;
}

template<typename T>
static std::vector<std::string> split_first(T &str, const std::string &del, const int pos) {
  std::vector<std::string> elements;
  std::string::size_type spos = str.find_first_of(del, 0);
  elements.emplace_back(str.substr(pos, spos));
  elements.emplace_back(str.substr(spos + del.length(), str.length() - spos - 1));
  return elements;
}

template<typename T>
static std::vector<std::string> split_CRLF(T &str, const std::string &del) {
  std::vector<std::string> elements;
  std::string::size_type pos = 0;
  std::string::size_type prev = 0;
  while ((pos = str.find(del, prev)) != std::string::npos) {
	elements.emplace_back(str.substr(prev, pos - prev + 1));
	prev = pos + 1;
  }
  return elements;
}

template<typename T>
static std::vector<std::string> split_first_CRLF(T &str, const std::string &del, const int pos) {
  std::vector<std::string> elements;
  std::string::size_type spos = str.find_first_of(del, 0);
  elements.emplace_back(str.substr(pos, spos));
  elements.emplace_back(str.substr(spos + del.length(), str.length() - spos - 1));
  return elements;
}
} // namespace utils

#endif //REDIS_STARTER_CPP_INCLUDE_UTILS_H_