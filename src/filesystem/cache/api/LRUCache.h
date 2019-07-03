#ifndef LOODB_LRUCACHE_H
#define LOODB_LRUCACHE_H

#include "Cache.h"

#include <list>
#include <map>

template<typename K, typename V>
class LRUCache : public Cache<K, V> {

public:

    explicit LRUCache(uint64_t);

private:

    class Impl;
    std::unique_ptr<Impl> impl_;
    
    std::unique_ptr<V> seek_impl(const K&) override;
    void update_impl(K, V) override;
};

#include "../impl/LRUCache.cpp"

#endif //LOODB_LRUCACHE_H
