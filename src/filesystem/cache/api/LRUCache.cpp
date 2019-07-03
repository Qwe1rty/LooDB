#include "LRUCache.h"
#include "../impl/LRUCacheImpl.h"

// TODO maybe find a way to do this with std::make_unique?
template<typename K, typename V>
LRUCache<K, V>::LRUCache(uint64_t limit) :
    Cache<K, V>(std::unique_ptr<typename Cache<K, V>::Impl>(
        new LRUCache<K, V>::Impl(limit)
    ))
{}