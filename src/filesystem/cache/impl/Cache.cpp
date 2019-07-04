#include "../api/Cache.h"


/*
 * Public member functions
 */

template<typename K, typename V>
std::unique_ptr<V> Cache<K, V>::seek(const K& key) {
    return strategy_->seek(key);
}

template<typename K, typename V>
void Cache<K, V>::update(K key, V value) {
    strategy_->update(std::move(key), std::move(value));
}


/*
 * Big 5
 */

template<typename K, typename V>
Cache<K, V>::Cache(const Cache& src) :
    strategy_{src.strategy_->clone()}
{}

template<typename K, typename V>
Cache<K, V>& Cache<K, V>::operator= (const Cache& src) {
    if (this != &src) {
        Cache temp(src);
        swap(temp);
    }
    return *this;
}

template<typename K, typename V>
Cache<K, V>::Cache(Cache&& src) noexcept :
    strategy_{std::move(src.strategy_)}
{}

template<typename K, typename V>
Cache<K, V>& Cache<K, V>::operator= (Cache&& src) noexcept {
    swap(src);
    return *this;
}

template<typename K, typename V>
void Cache<K, V>::swap(Cache& src) noexcept {
    using std::swap;
    swap(strategy_, src.strategy_);
}


/*
 * Constructors/Destructors
 */

template<typename K, typename V>
Cache<K, V>::Cache(const CacheStrategy<K, V>& strategy) :
    strategy_{strategy.clone()}
{}

template<typename K, typename V>
Cache<K, V>::Cache(CacheStrategy<K, V>&& strategy) :
    strategy_{strategy.move()}
{}

template<typename K, typename V>
Cache<K, V>::~Cache() = default;