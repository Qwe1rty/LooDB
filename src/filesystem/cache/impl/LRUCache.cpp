#include "../api/LRUCache.h"

#include <list>
#include <unordered_map>


template<typename K, typename V>
class LRUCache<K, V>::Impl {

public:

    explicit Impl(uint64_t);

    std::unique_ptr<V> read(const K&);
    void write(K, V);

private:

    using CachePair      = std::pair<K, V>;
    using CacheList      = std::list<CachePair>;
    using CacheListEntry = typename CacheList::iterator;
    using CacheMap       = std::unordered_map<K, CacheListEntry>;

    uint64_t limit_;
    CacheList queue_;
    CacheMap table_;

    bool contains(const K& key) const;
    void refresh(const K& key);
};


/*
 * Public member functions
 */

template<typename K, typename V>
std::unique_ptr<V> LRUCache<K, V>::Impl::read(const K& key) {

    if (contains(key)) {
        refresh(key);
        return std::make_unique<V>(queue_.front().second);
    }

    return nullptr;
}

template<typename K, typename V>
void LRUCache<K, V>::Impl::write(K key, V value) {

    if (contains(key)) {
        refresh(key);
        queue_.front().second = std::move(value);
        return;
    }

    if (table_.size() >= limit_) {
        table_.erase(queue_.rbegin()->first);
        queue_.pop_back();
    }

    queue_.emplace_front(std::make_pair(
        key,
        std::move(value)
    ));
    table_.insert(std::make_pair(
        std::move(key),
        queue_.begin()
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
    queue_.erase(entry);
    queue_.emplace_front(std::move(*entry));

    // entry has been invalidated, so get begin();
    table_.at(key) = queue_.begin();
}


/*
 * Constructors/Destructors
 */

template<typename K, typename V>
LRUCache<K, V>::Impl::Impl(uint64_t limit) :
    limit_{limit},
    queue_{},
    table_{}
{}


/*
 * NVI/PIMPL Boilerplate
 */

template<typename K, typename V>
std::unique_ptr<V> LRUCache<K, V>::seek_impl(const K& key) {
    return impl_->read(key);
}

template<typename K, typename V>
void LRUCache<K, V>::update_impl(K key, V value) {
    impl_->write(key, value);
}

template<typename K, typename V>
LRUCache<K, V>::LRUCache(uint64_t limit) :
    impl_(std::make_unique<Impl>(limit))
{}