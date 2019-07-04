#ifndef LOODB_CACHESTRATEGY_H
#define LOODB_CACHESTRATEGY_H

#include "Cache.h"

#include <memory>


template<typename K, typename V>
class Cache;

template<typename K, typename V>
class CacheStrategy {

public:

    CacheStrategy() = default;
    virtual ~CacheStrategy() = 0;

private:

    virtual std::unique_ptr<V> seek(const K&) = 0;
    virtual void update(K, V) = 0;


    virtual std::unique_ptr<CacheStrategy> clone() = 0;
    virtual std::unique_ptr<CacheStrategy> move() noexcept = 0;

    CacheStrategy(const CacheStrategy&) = delete;
    CacheStrategy(CacheStrategy&&) noexcept = delete;

    CacheStrategy& operator= (const CacheStrategy&) = delete;
    CacheStrategy& operator= (CacheStrategy&&) noexcept = delete;

    friend Cache<K, V>;
};

#include "../impl/CacheStrategy.cpp"

#endif //LOODB_CACHESTRATEGY_H
