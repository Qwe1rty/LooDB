#include "ByteWriter.h"


class ByteWriter::Impl {

public:

  template<typename Numeric>
  void write(const Numeric&);

  void seek(uint32_t);

  Impl(char* const&, uint32_t);

private:

  char* const bytes_;
  uint32_t offset_;
  // TODO: implement limits + possible vectorization?
};


/*
 * ByteWriter.h constructors
 */

ByteWriter::ByteWriter(char* const& bytes, uint32_t offset) :
  impl_{std::make_unique<Impl>(bytes, offset)}

{}

ByteWriter::ByteWriter(const std::unique_ptr<char[]>& bytes, uint32_t offset) :
  impl_{std::make_unique<Impl>(bytes.get(), offset)}
{}

ByteWriter::ByteWriter(const std::unique_ptr<char*>& bytes, uint32_t offset) :
  impl_{std::make_unique<Impl>(*bytes, offset)}
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


/*
 * Implementations
 */

ByteWriter::Impl::Impl(char* const& bytes, uint32_t offset) :
  bytes_{bytes},
  offset_{offset}
{}

template<typename Numeric>
void ByteWriter::Impl::write(const Numeric& item) {
  for (uint32_t i = 0; i < sizeof(item); ++i) {
    bytes_[offset_ + i] = (item >> i * 8);
  }
  offset_ += sizeof(item);
}

void ByteWriter::Impl::seek(uint32_t offset) {
  offset_ = offset;
}