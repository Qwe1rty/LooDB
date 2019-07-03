#include "../filesystem/cache/api/Cache.h"
#include "../filesystem/cache/api/LRUCache.h"

#include <iostream>

std::ostream& operator<< (std::ostream& os, std::nullptr_t ptr) {
    return os << "nullptr";
}

int main() {

    using K = int;
    using V = int;

    using PageCache = LRUCache<K, V>;
    std::unique_ptr<Cache<K, V>> cache = std::make_unique<PageCache>(5);

    cache->update(1, 100);
    cache->update(2, 200);

    std::unique_ptr<V> test;

    test = cache->seek(1);
    std::cout << *test << std::endl;
    test = cache->seek(3);
    std::cout << *test << std::endl;

    cache->update(3, 300);
    cache->update(4, 400);
    cache->update(5, 500);
    cache->update(6, 600);

    test = cache->seek(2);
    std::cout << *test << std::endl;

}