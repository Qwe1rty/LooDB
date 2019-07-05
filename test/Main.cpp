#include "../src/filesystem/cache/api/Cache.h"
#include "../src/filesystem/cache/api/LRUCacheStrategy.h"

#include <iostream>


std::ostream& operator<< (std::ostream& out, const std::unique_ptr<int>& ptr) {
    out << (ptr ? std::to_string(*ptr) : "nullptr");
    return out;
}

int main() {

    using K = int;
    using V = int;

    Cache<K, V> cache{LRUCacheStrategy<int, int>(5)};
    std::unique_ptr<V> test;

    // First test basic cache operations
    cache.update(1, 100);
    cache.update(2, 200);

    test = cache.seek(1);
    std::cout << test << std::endl; // 100
    test = cache.seek(3);
    std::cout << test << std::endl; // nullptr

    cache.update(3, 300);
    cache.update(4, 400);
    cache.update(5, 500);
    cache.update(6, 600);

    test = cache.seek(2);
    std::cout << test << std::endl; // nullptr
    test = cache.seek(1);
    std::cout << test << std::endl; // 100

    cache.update(6, 60000);
    test = cache.seek(6);
    std::cout << test << std::endl; // 60000

    // Divider, testing big 5 operations
    std::cout << std::endl;

    Cache<K, V> cash{cache};

    cash.update(8, 88);

    test = cache.seek(8);
    std::cout << test << std::endl; // nullptr
    test = cash.seek(8);
    std::cout << test << std::endl; // 88

    cache = std::move(cash);

    cache.update(22, 22222);
    test = cache.seek(22);
    std::cout << test << std::endl; // 22222

    cash.update(11, 11111); // may or may not segfault, has been moved
}