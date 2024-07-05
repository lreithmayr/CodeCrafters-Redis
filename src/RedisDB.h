#ifndef REDIS_STARTER_CPP_SRC_REDISDB_H_
#define REDIS_STARTER_CPP_SRC_REDISDB_H_

#include <unordered_map>
#include <string>

class RedisDB {
 public:
  RedisDB() = default;

  template <typename T>
  void insert(T &val);

  template <typename T>
  T& get(const T &key);

 private:
  std::unordered_map<std::string, std::string> m_redis_db;
};

#endif //REDIS_STARTER_CPP_SRC_REDISDB_H_
