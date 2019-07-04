#include "../api/LRUCacheStrategy.h"

#include <list>
#include <unordered_map>


template<typename K, typename V>
class LRUCacheStrategy<K, V>::Impl {

    using CachePair      = std::pair<K, V>;
    using CacheList      = std::list<CachePair>;
    using CacheListEntry = typename CacheList::iterator;
    using CacheMap       = std::unordered_map<K, CacheListEntry>;

public:

    std::unique_ptr<V> seek(const K&);
    void update(K, V);


    explicit Impl(uint64_t);

    Impl(const Impl&);
    Impl(Impl&&) noexcept;

private:

    uint64_t limit_;
    CacheList queue_;
    CacheMap table_;

    bool contains(const K& key) const;
    void refresh(const K& key);
};


/*
 * LRUCacheStrategy.h header class implementations
 */

template<typename K, typename V>
std::unique_ptr<V> LRUCacheStrategy<K, V>::seek(const K& key) {
    return impl_->seek(key);
}

template<typename K, typename V>
void LRUCacheStrategy<K, V>::update(K key, V value) {
    impl_->update(key, value);
}


template<typename K, typename V>
std::unique_ptr<CacheStrategy<K, V>> LRUCacheStrategy<K, V>::clone() {

    return std::unique_ptr<LRUCacheStrategy<K, V>>(new LRUCacheStrategy<K, V>(*this));
}

template<typename K, typename V>
std::unique_ptr<CacheStrategy<K, V>> LRUCacheStrategy<K, V>::move() noexcept {

    return std::unique_ptr<LRUCacheStrategy<K, V>>(new LRUCacheStrategy<K, V>(std::move(*this)));
}

<<<<<<< HEAD

=======
>>>>>>> Major cache refactoring, now supports all copy/move operations and can be instantiated on stack
template<typename K, typename V>
LRUCacheStrategy<K, V>::LRUCacheStrategy(const LRUCacheStrategy& src) :
    impl_(std::unique_ptr<Impl>(new Impl(*src.impl_)))
{}

template<typename K, typename V>
LRUCacheStrategy<K, V>::LRUCacheStrategy(LRUCacheStrategy&& src) noexcept :
    impl_(std::move(src.impl_))
{}

template<typename K, typename V>
LRUCacheStrategy<K, V>::LRUCacheStrategy(uint64_t limit) :
    CacheStrategy<K, V>(),
    impl_(std::make_unique<Impl>(limit))
{}


/*
 * Public member functions
 */

template<typename K, typename V>
std::unique_ptr<V> LRUCacheStrategy<K, V>::Impl::seek(const K& key) {

    if (contains(key)) {
        refresh(key);
        return std::make_unique<V>(queue_.front().second);
    }

    return nullptr;
}

template<typename K, typename V>
void LRUCacheStrategy<K, V>::Impl::update(K key, V value) {

    if (contains(key)) {
        refresh(key);
        queue_.front().second = std::move(value);
        return;
    }

    if (table_.size() >= limit_) {
        table_.erase(queue_.back().first);
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
bool LRUCacheStrategy<K, V>::Impl::contains(const K& key) const {

    return table_.find(key) != table_.end();
}

template<typename K, typename V>
void LRUCacheStrategy<K, V>::Impl::refresh(const K& key) {

    CacheListEntry entry = table_.at(key);
    queue_.erase(entry);
    queue_.emplace_front(std::move(*entry));
    table_.at(key) = queue_.begin();
}


/*
 * Constructors/Destructors
 */

template<typename K, typename V>
LRUCacheStrategy<K, V>::Impl::Impl(uint64_t limit) :
    limit_{limit},
    queue_{},
    table_{}
{}

template<typename K, typename V>
LRUCacheStrategy<K, V>::Impl::Impl(const Impl& src) :
    limit_{src.limit_},
    queue_{src.queue_},
    table_{src.table_}
{}

template<typename K, typename V>
LRUCacheStrategy<K, V>::Impl::Impl(Impl&& src) noexcept :
    limit_{src.limit_},
    queue_{std::move(src.queue_)},
    table_{std::move(src.table_)}
{}