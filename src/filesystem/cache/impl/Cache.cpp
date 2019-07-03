#include "../api/Cache.h"


/*
 * Public member functions
 */

template<typename K, typename V>
std::unique_ptr<V> Cache<K, V>::seek(const K& key) {
    return seek_impl(key);
}

template<typename K, typename V>
void Cache<K, V>::update(K key, V value) {
    update_impl(std::move(key), std::move(value));
}


/*
 * Constructors/Destructors
 */

template<typename K, typename V>
Cache<K, V>::Cache() = default;

template<typename K, typename V>
Cache<K, V>::~Cache() = default;