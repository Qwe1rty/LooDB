#include "../api/Pager.h"
#include "../api/PageCodec.h"
#include "../../../cache/api/Cache.h"
#include "../../../cache/api/LRUCacheStrategy.h"

#include <fstream>


class Pager::Impl final {

//    using PageCache         = Cache<uint64_t, std::unique_ptr<Page>>;
//    using PageCacheStrategy = LRUCacheStrategy<uint64_t, std::unique_ptr<Page>>;

public:

    explicit Impl(std::string, uint64_t = DEFAULT_CACHE_LIMIT);
    ~Impl();

    std::unique_ptr<Page> read(uint64_t);
    void write(uint64_t, const std::unique_ptr<Page>&);

private:

//    PageCache cache_;
    std::string filename_;
    std::fstream stream_;
};

void Pager::ImplDeleter::operator()(Pager::Impl* impl) {
  delete impl;
}


/*
 * Pager.h header class implementations
 */

std::unique_ptr<Page> Pager::read(uint64_t index) {
    return impl_->read(index);
}

void Pager::write(uint64_t index, const std::unique_ptr<Page>& page) {
    impl_->write(index, page);
}

Pager::Pager(std::string filename, uint64_t limit) :
    impl_{std::unique_ptr<Impl, ImplDeleter>(new Impl(filename, limit))}
{}


/*
 * Public member functions
 */

std::unique_ptr<Page> Pager::Impl::read(uint64_t index) {

    // First check the cache
//    auto cache_result{cache_.seek(index)};
//    if (cache_result) return std::move(*cache_result);

    // Next do a disk seek
    auto disk_result = std::array<char, Page::SIZE>{};
    stream_.seekg(index * Page::SIZE);
    stream_.read(disk_result.data(), Page::SIZE);

    return PageCodec::CODEC.decode(disk_result);
}

void Pager::Impl::write(uint64_t index, const std::unique_ptr<Page>& page) {

     // Try to write to disk first, in case of errors
     auto page_bytes = PageCodec::CODEC.encode(page);
     stream_.seekg(index * Page::SIZE);
     stream_.write(page_bytes.data(), Page::SIZE);

     // Now update the cache
//     cache_.update(index, std::move(page));
}


/*
 * Constructors/Destructors
 */

Pager::Impl::Impl(std::string filename, uint64_t limit) :
//    cache_{PageCache{PageCacheStrategy{limit}}},
    filename_{std::move(filename)},
    stream_{}
{
    stream_.open(filename, std::fstream::in | std::fstream::out);
}

Pager::Impl::~Impl() {
    stream_.close();
}