#include "ByteWriter.h"


class ByteWriter::Impl {

public:

  template<typename Numeric>
  void write(const uint32_t& offset, const Numeric&) const;

  explicit Impl(char* const&);

private:

  char* const bytes_;
};


/*
 * ByteWriter.h constructors
 */

ByteWriter::ByteWriter(char* const& bytes) :
  impl_{std::make_unique<Impl>(bytes)}
{}

ByteWriter::ByteWriter(const std::unique_ptr<char[]>& bytes) :
  impl_{std::make_unique<Impl>(bytes.get())}
{}

ByteWriter::ByteWriter(const std::unique_ptr<char*>& bytes) :
  impl_{std::make_unique<Impl>(*bytes)}
{}


/*
 * ByteWriter.h public methods
 */

void ByteWriter::write(const uint32_t& offset, const char& item) const {
  impl_->write<unsigned char>(offset, item);
}

void ByteWriter::write(const uint32_t& offset, const uint32_t& item) const {
  impl_->write<uint32_t>(offset, item);
}

void ByteWriter::write(const uint32_t& offset, const uint64_t& item) const {
  impl_->write<uint64_t>(offset, item);
}


/*
 * Implementations
 */

ByteWriter::Impl::Impl(char* const& bytes) :
  bytes_{bytes}
{}

template<typename Numeric>
void ByteWriter::Impl::write(const uint32_t& offset, const Numeric& item) const {
  for (uint32_t i = 0; i < sizeof(item); ++i) {
    bytes_[offset + i] = (item >> i * 8);
  }
}