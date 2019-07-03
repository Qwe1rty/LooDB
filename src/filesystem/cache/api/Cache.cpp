#include "Cache.h"
#include "../impl/CacheImpl.h"

template<typename K, typename V>
Cache<K, V>::Cache(std::unique_ptr<Impl> impl) :
    impl_{std::move(impl)}
{}

template<typename K, typename V>
Cache<K, V>::~Cache() = default;


/*
 * Public member functions
 */

template<typename K, typename V>
std::unique_ptr<V> Cache<K, V>::seek(const K& key) {
    return impl_->seek(key);
}

template<typename K, typename V>
void Cache<K, V>::update(K key, V value) {
    impl_->update(std::move(key), std::move(value));
}