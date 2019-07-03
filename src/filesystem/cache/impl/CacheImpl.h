#ifndef LOODB_CACHEIMPL_H
#define LOODB_CACHEIMPL_H

#include "../api/Cache.h"

template<typename K, typename V>
class Cache<K, V>::Impl {

public:

    virtual std::unique_ptr<V> seek(const K&) = 0;
    virtual void update(K, V) = 0;


    Impl() = default;

    Impl(const Impl&) = delete;
    Impl& operator= (const Impl&) = delete;

    Impl(Impl&&) noexcept = default;
    Impl& operator= (Impl&&) noexcept = default;

    virtual ~Impl() = 0;
};

#include "CacheImpl.cpp"

#endif //LOODB_CACHEIMPL_H
