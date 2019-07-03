#ifndef LOODB_LRUCACHEIMPL_H
#define LOODB_LRUCACHEIMPL_H

#include "../api/LRUCache.h"

#include <list>
#include <unordered_map>

template<typename K, typename V>
class LRUCache<K, V>::Impl : public Cache<K, V>::Impl {

public:

    explicit Impl(uint64_t);

    std::unique_ptr<V> seek(const K&) override;
    void update(K, V) override;

private:

    using CachePair      = std::pair<K, V>;
    using CacheList      = std::list<CachePair>;
    using CacheListEntry = typename CacheList::iterator;
    using CacheMap       = std::unordered_map<K, CacheListEntry>;

    uint64_t limit_;
    CacheList queue_;
    CacheMap table_;

    bool contains(const K& key) const;
    void refresh(const K& key);
};

#include "LRUCacheImpl.cpp"

#endif //LOODB_LRUCACHEIMPL_H
