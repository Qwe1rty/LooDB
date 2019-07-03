#include "LRUCache.h"

template<typename K, typename V>
LRUCache<K, V>::LRUCache(uint64_t limit) :
    Cache<K, V>::Cache(std::make_unique<Impl>(limit))
{}