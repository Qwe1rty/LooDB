#include "../api/ByteWriter.h"


class ByteWriter::Impl {

public:

  template<typename Numeric>
  void write(const Numeric&);

  void seek(uint32_t);

  uint32_t limit() const;
  uint32_t offset() const;

  Impl(char* const&, uint32_t limit, uint32_t offset);

private:

  char* const bytes_;
  const uint32_t limit_;
  uint32_t offset_;
  // TODO: possible vectorization?
};


/*
 * ByteWriter.h constructors
 */

ByteWriter::ByteWriter(char* const& bytes, uint32_t limit, uint32_t offset) :
  impl_{std::make_unique<Impl>(bytes, limit, offset)}

{}

ByteWriter::ByteWriter(const std::unique_ptr<char[]>& bytes, uint32_t limit, uint32_t offset) :
  impl_{std::make_unique<Impl>(bytes.get(), limit, offset)}
{}

ByteWriter::ByteWriter(const std::unique_ptr<char*>& bytes, uint32_t limit, uint32_t offset) :
  impl_{std::make_unique<Impl>(*bytes, limit, offset)}
{}


/*
 * ByteWriter.h public methods
 */

ByteWriter& ByteWriter::operator<<(const char& item) {
  impl_->write<unsigned char>(item);
  return *this;
}

ByteWriter& ByteWriter::operator<<(const uint32_t& item) {
  impl_->write<uint32_t>(item);
  return *this;
}

ByteWriter& ByteWriter::operator<<(const uint64_t& item) {
  impl_->write<uint64_t>(item);
  return *this;
}

void ByteWriter::seek(uint32_t offset) {
  impl_->seek(offset);
}

uint32_t ByteWriter::limit() const {
  return impl_->limit();
}

uint32_t ByteWriter::offset() const {
  return impl_->offset();
}

ByteWriter::operator bool() const {
  return (limit() - offset()) > 1;
}


/*
 * Implementations
 */

ByteWriter::Impl::Impl(char* const& bytes, uint32_t limit, uint32_t offset) :
  bytes_{bytes},
  limit_{limit},
  offset_{offset}
{
  if (offset_ >= limit_) {
    throw std::invalid_argument("Limit value: " +
                                std::to_string(limit_) +
                                ", must be greater than the offset: " +
                                std::to_string(offset_));
  }
}

template<typename Numeric>
void ByteWriter::Impl::write(const Numeric& item) {

  auto item_size{sizeof(item)};

  if (offset_ + item_size >= limit_) {
    throw std::out_of_range("Limit will be reached for item of size: " +
                            std::to_string(item_size) +
                            ", with current offset: " +
                            std::to_string(offset_) +
                            ", and limit: " +
                            std::to_string(limit_));
  }

  for (uint32_t i = 0; i < item_size; ++i) {
    bytes_[offset_] = (item >> i * 8);
    ++offset_;
  }
}

void ByteWriter::Impl::seek(uint32_t offset) {

  if (offset < limit_) offset_ = offset;
  throw std::out_of_range("Offset value " +
                          std::to_string(offset) +
                          " is not below the limit: " +
                          std::to_string(limit_));
}

uint32_t ByteWriter::Impl::limit() const {
  return limit_;
}

uint32_t ByteWriter::Impl::offset() const {
  return offset_;
}