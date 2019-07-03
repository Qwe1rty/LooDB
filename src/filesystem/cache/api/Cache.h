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

    Cache();
    virtual ~Cache() = 0;

private:

    virtual std::unique_ptr<V> seek_impl(const K&) = 0;
    virtual void update_impl(K, V) = 0;
};

#include "../impl/Cache.cpp"

#endif //LOODB_CACHE_H
