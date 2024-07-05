#ifndef REDIS_STARTER_CPP_SRC_REDISDB_H_
#define REDIS_STARTER_CPP_SRC_REDISDB_H_

#include <unordered_map>
#include <string>

template<typename K, typename V>
class RedisDB {
 public:
  RedisDB() = default;

  void insert(const K &key, const V &val);
  V& get(const K &key);

 private:
  std::unordered_map<K, V> m_redis_db;
};

#endif //REDIS_STARTER_CPP_SRC_REDISDB_H_
