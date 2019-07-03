#include "LRUCacheImpl.h"

template<typename K, typename V>
LRUCache<K, V>::Impl::Impl(uint64_t limit) :
    limit_{limit},
    queue_{},
    table_{}
{}

/*
 * Public member functions
 */

template<typename K, typename V>
std::unique_ptr<V> LRUCache<K, V>::Impl::seek(const K& key) {

    if (contains(key)) {
        refresh(key);
        return std::make_unique<V>(queue_.front()->second);
    }

    return nullptr;
}

template<typename K, typename V>
void LRUCache<K, V>::Impl::update(K key, V value) {

    if (contains(key)) {
        refresh(key);
        return;
    }

    if (table_.size >= limit_) {
        table_.erase(queue_.back()->first);
        queue_.pop_back();
    }

    queue_.emplace_front(std::make_pair<K, V>(
        key,
        std::move(value)
    ));
    table_.insert(std::make_pair<K, CacheListEntry>(
        std::move(key),
        queue_.front()
    ));
}

/*
 * Private member functions
 */

template<typename K, typename V>
bool LRUCache<K, V>::Impl::contains(const K& key) const {

    return table_.find(key) != table_.end();
}

template<typename K, typename V>
void LRUCache<K, V>::Impl::refresh(const K& key) {

    CacheListEntry entry = table_.at(key);
    queue_.emplace_front(std::move(*entry));
    queue_.erase(entry);

    // entry has been invalidated, so get front();
    CacheListEntry front = queue_.front();
    table_.at(key) = front;
    return front;
}