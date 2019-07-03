#include "Cache.h"

template<typename K, typename V>
Cache<K, V>::Cache(std::unique_ptr<Impl> impl) :
    impl_{impl}
{}

/*
 * Public member functions
 */

template<typename K, typename V>
std::unique_ptr<V> Cache<K, V>::seek(const K& key) {
    return impl_->seek_impl(key);
}

template<typename K, typename V>
void Cache<K, V>::update(K key, V value) {
    impl_->update_impl(std::move(key), std::move(value));
}