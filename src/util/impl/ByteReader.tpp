#include "../api/ByteReader.h"


template<typename Datatype>
class ByteReader<Datatype>::Impl {

public:

  template<typename Numeric>
  void read(Numeric&);

  uint32_t limit() const;
  uint32_t offset() const;

  void skip(uint32_t);

  Impl(Datatype&, uint32_t limit, uint32_t offset);

private:

  const Datatype& bytes_;
  const uint32_t limit_;
  uint32_t offset_;
};


/*
 * ByteWriter.h implementation
 */

template<typename Datatype>
ByteReader<Datatype>::ByteReader(const Datatype& bytes, uint32_t limit, uint32_t offset) :
  impl_{std::make_unique<Impl>(bytes, limit, offset)}
{}

template<typename Datatype>
ByteReader<Datatype>& ByteReader<Datatype>::operator>>(char& item) {
  impl_->template read<char>(item);
  return *this;
}

template<typename Datatype>
ByteReader<Datatype>& ByteReader<Datatype>::operator>>(bool& item) {
  impl_->template read<bool>(item);
  return *this;
}

template<typename Datatype>
ByteReader<Datatype>& ByteReader<Datatype>::operator>>(uint32_t& item) {
  impl_->template read<uint32_t>(item);
  return *this;
}

template<typename Datatype>
ByteReader<Datatype>& ByteReader<Datatype>::operator>>(uint64_t& item) {
  impl_->template read<uint64_t>(item);
  return *this;
}

template<typename Datatype>
void ByteReader<Datatype>::skip(uint32_t skip) {
  impl_->skip(skip);
}

template<typename Datatype>
uint32_t ByteReader<Datatype>::limit() const {
  return impl_->limit();
}

template<typename Datatype>
uint32_t ByteReader<Datatype>::offset() const {
  return impl_->offset();
}


/*
 * Implementations
 */

template<typename Datatype>
ByteReader<Datatype>::Impl::Impl(Datatype& bytes, uint32_t limit, uint32_t offset) :
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

template<typename Datatype>
template<typename Numeric>
void ByteReader<Datatype>::Impl::read(Numeric& item) {

  auto item_size{sizeof(item)};

  if (offset_ + item_size >= limit_) {
    throw std::out_of_range("Limit will be reached for item of size: " +
                            std::to_string(item_size) +
                            ", with current offset: " +
                            std::to_string(offset_) +
                            ", and limit: " +
                            std::to_string(limit_));
  }

  item = 0;
  for (uint32_t i = 0; i < item_size; ++i) {
    item |= static_cast<Numeric>(static_cast<unsigned char>(bytes_[offset_]) << (i * 8));
    ++offset_;
  }
}

template<typename Datatype>
void ByteReader<Datatype>::Impl::skip(uint32_t skip) {

  if (offset_ + skip < limit_) offset_ += skip;
  else throw std::out_of_range("Current offset value " +
                          std::to_string(offset_) +
                          " cannot be incremented by " +
                          std::to_string(skip) +
                          ", as it will surpass the limit: " +
                          std::to_string(limit_));
}

template<typename Datatype>
uint32_t ByteReader<Datatype>::Impl::limit() const {
  return limit_;
}

template<typename Datatype>
uint32_t ByteReader<Datatype>::Impl::offset() const {
  return offset_;
}
