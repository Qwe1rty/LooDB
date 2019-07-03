#ifndef LOODB_CACHE_H
#define LOODB_CACHE_H

#include <memory>

template<typename K, typename V>
class Cache {

public:

    // Returns the value V on cache miss, returns null on cache miss
    std::unique_ptr<V> seek(const K&);

    // Updates a K-V pair: will insert the new pair if previous mapping is not found
    void update(K, V);


    Cache(const Cache&) = delete;
    Cache& operator= (const Cache&) = delete;

    Cache(Cache&&) noexcept = default;
    Cache& operator= (Cache&&) noexcept = default;

    virtual ~Cache() = 0;

protected:

    class Impl;
    std::unique_ptr<Impl> impl_;

    explicit Cache(std::unique_ptr<Impl>);
};

#include "Cache.cpp"

#endif //LOODB_CACHE_H
