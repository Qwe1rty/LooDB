#ifndef LOODB_CACHE_H
#define LOODB_CACHE_H

#include "CacheStrategy.h"

#include <memory>

template<typename K, typename V>
class Cache {

public:

    // Returns the value V on cache miss, returns null on cache miss
    std::unique_ptr<V> seek(const K&);

    // Updates a K-V pair: will insert the new pair if previous mapping is not found
    void update(K, V);

    // Swaps two caches
    void swap(Cache&) noexcept;


    Cache(const CacheStrategy<K, V>&);
    Cache(CacheStrategy<K, V>&&);

    Cache(const Cache&);
    Cache(Cache&&) noexcept;

    Cache& operator= (const Cache&);
    Cache& operator= (Cache&&) noexcept;

    ~Cache();

private:

    std::unique_ptr<CacheStrategy<K, V>> strategy_;
};

#include "../impl/Cache.tpp"

#endif //LOODB_CACHE_H
