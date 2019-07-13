#include "../api/Pager.h"
#include "../api/PageCodec.h"
#include "../../../cache/api/Cache.h"
#include "../../../cache/api/LRUCacheStrategy.h"

#include "../../page/impl/Page.cpp"

#include <fstream>


class Pager::Impl final {

    using PageCache         = Cache<uint64_t, Page>;
    using PageCacheStrategy = LRUCacheStrategy<uint64_t, Page>;

public:

    explicit Impl(std::string, uint64_t = DEFAULT_CACHE_LIMIT);
    ~Impl();

    Page read(uint64_t);
    void write(uint64_t, Page);

private:

    PageCache cache_;
    std::string filename_;
    std::fstream stream_;
};


/*
 * Pager.h header class implementations
 */

Page Pager::read(uint64_t index) {
    return impl_->read(index);
}

void Pager::write(uint64_t index, Page page) {
    impl_->write(index, page);
}

Pager::Pager(std::string filename, uint64_t limit) :
    impl_{std::make_unique<Impl>(filename, limit)}
{}


/*
 * Public member functions
 */

Page Pager::Impl::read(uint64_t index) {

    // First check the cache
//    auto cache_result{cache_.seek(index)};
//    if (cache_result) return std::move(*cache_result);

    // Next do a disk seek
    auto disk_result = std::unique_ptr<char[]>{new char[Page::PAGE_SIZE]};
    stream_.seekg(index * Page::PAGE_SIZE);
    stream_.read(disk_result.get(), Page::PAGE_SIZE);

    return Page::PAGE_CODEC.decode(std::move(disk_result));
}

void Pager::Impl::write(uint64_t index, Page page) {

     // Try to write to disk first, in case of errors
     auto page_bytes = Page::PAGE_CODEC.encode(page);
     stream_.seekg(index * Page::PAGE_SIZE);
     stream_.write(page_bytes.get(), Page::PAGE_SIZE);

     // Now update the cache
//     cache_.update(index, std::move(page));
}


/*
 * Constructors/Destructors
 */

Pager::Impl::Impl(std::string filename, uint64_t limit) :
    cache_{PageCache{PageCacheStrategy{limit}}},
    filename_{std::move(filename)},
    stream_{}
{
    stream_.open(filename, std::fstream::in | std::fstream::out);
}

Pager::Impl::~Impl() {
    stream_.close();
}