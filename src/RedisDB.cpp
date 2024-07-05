#include "RedisDB.h"

template<typename T>
void RedisDB::insert(T &val) {
  m_redis_db.insert(val);
}

template<typename T>
T &RedisDB::get(const T &key) {
  return m_redis_db.at(key);
}
