#include "RedisDB.h"

template<typename K, typename V>
void RedisDB<K, V>::insert(const K &key, const V &val) {
  m_redis_db.insert({ key, val });
}

template<typename K, typename V>
V &RedisDB<K, V>::get(const K &key) {
  return m_redis_db.at(key);
}
