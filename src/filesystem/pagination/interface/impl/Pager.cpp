#include "../api/Pager.h"
#include "../api/PageCodec.h"
#include "../../../cache/api/Cache.h"
#include "../../../cache/api/LRUCacheStrategy.h"

#include <fstream>


class Pager::Impl final {

//  using PageCache         = Cache<uint64_t, std::unique_ptr<Page>>;
//  using PageCacheStrategy = LRUCacheStrategy<uint64_t, std::unique_ptr<Page>>;

public:

  explicit Impl(const std::string&, uint32_t = DEFAULT_CACHE_LIMIT);
  ~Impl();

  std::unique_ptr<Page> read(uint32_t);
  void write(uint32_t, const std::unique_ptr<Page>&);
  uint32_t length();

private:

//  PageCache cache_;
  std::string filename_;
  std::fstream stream_;
};

// https://stackoverflow.com/questions/9954518/stdunique-ptr-with-an-incomplete-type-wont-compile
void Pager::ImplDeleter::operator()(Pager::Impl* impl) {
  delete impl;
}


/*
 * Pager.h header class implementations
 */

template<typename T>
std::unique_ptr<T> Pager::fetch(uint32_t page_index) {
  return std::unique_ptr<T>(static_cast<T*>(read(page_index).release()));
}

std::unique_ptr<Page> Pager::read(uint32_t index) {
  return impl_->read(index);
}

void Pager::write(uint32_t index, const std::unique_ptr<Page>& page) {
  impl_->write(index, page);
}

void Pager::append(const std::unique_ptr<Page>& page) {
  impl_->write(size(), page);
}

uint32_t Pager::length() const {
  return impl_->length();
}

uint32_t Pager::size() const {
  return length() / Page::SIZE;
}

Pager::Pager(const std::string& filename, uint32_t limit) :
  impl_{std::unique_ptr<Impl, ImplDeleter>(new Impl(filename, limit))}
{}


/*
 * Public member functions
 */

std::unique_ptr<Page> Pager::Impl::read(uint32_t index) {

  // First check the cache
//  auto cache_result{cache_.seek(index)};
//  if (cache_result) return std::move(*cache_result);

  // Next do a disk seek
  auto disk_result = std::array<char, Page::SIZE>{};
  stream_.seekg(index * Page::SIZE);
  stream_.read(disk_result.data(), Page::SIZE);

  return PageCodec::CODEC.decode(disk_result);
}

void Pager::Impl::write(uint32_t index, const std::unique_ptr<Page>& page) {

   // Try to write to disk first, in case of errors
   auto page_bytes = PageCodec::CODEC.encode(page);
   stream_.seekp(index * Page::SIZE);
   stream_.write(page_bytes.data(), Page::SIZE);

   // Now update the cache
//   cache_.update(index, std::move(page));
}

uint32_t Pager::Impl::length() {

  const uint32_t prev = stream_.tellg();

  stream_.seekg(0, std::fstream::end);
  const uint32_t size = stream_.tellg();
  stream_.seekg(prev, std::fstream::beg);

  return size;
}


/*
 * Constructors/Destructors
 */

Pager::Impl::Impl(const std::string& filename, uint32_t limit) :
//  cache_{PageCache{PageCacheStrategy{limit}}},
  filename_{filename},
  stream_{filename, std::fstream::in |
                    std::fstream::out |
                    std::fstream::binary}
{
  // If the file does NOT exist, then the .good() function will return false.
  // If the file does exist, the stream will already be initialized with the two-way
  //   stream open.

  if (!stream_.good()) {

    // Create file without writing anything into it
    stream_.open(filename, std::fstream::out | std::fstream::binary);
    stream_.close();

    // Try and open with std::fstream::in flag, preventing overwriting of old data
    stream_.open(filename, std::fstream::in |
                           std::fstream::out |
                           std::fstream::binary);
  }

  // The exceptions flag is turned on after the above if statement, otherwise
  //   an exception is thrown immediately after checking .good()
  stream_.exceptions(std::ofstream::failbit | std::ofstream::badbit);
}

Pager::Impl::~Impl() {
  stream_.close();
}