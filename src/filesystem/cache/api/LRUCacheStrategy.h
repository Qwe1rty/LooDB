#ifndef LOODB_LRUCACHESTRATEGY_H
#define LOODB_LRUCACHESTRATEGY_H

#include "Cache.h"
#include "CacheStrategy.h"

#include <list>
#include <map>


template<typename K, typename V>
class LRUCacheStrategy : public CacheStrategy<K, V> {

public:

    explicit LRUCacheStrategy(uint64_t);

private:

    class Impl;
    std::unique_ptr<Impl> impl_;

    std::unique_ptr<V> seek(const K&) override;
    void update(K, V) override;


    std::unique_ptr<CacheStrategy<K, V>> clone() override;
    std::unique_ptr<CacheStrategy<K, V>> move() noexcept override;

    LRUCacheStrategy(const LRUCacheStrategy&);
    LRUCacheStrategy(LRUCacheStrategy&&) noexcept;

    LRUCacheStrategy& operator= (const LRUCacheStrategy&) = delete;
    LRUCacheStrategy& operator= (LRUCacheStrategy&&) noexcept = delete;
};

#include "../impl/LRUCacheStrategy.cpp"

#endif //LOODB_LRUCACHESTRATEGY_H
