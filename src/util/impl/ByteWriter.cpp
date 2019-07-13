#include "../api/ByteWriter.h"


template<typename Datatype>
class ByteWriter<Datatype>::Impl {

public:

  template<typename Numeric>
  void write(const Numeric&);

  void seek(uint32_t);

  uint32_t limit() const;
  uint32_t offset() const;

  Impl(Datatype&, uint32_t limit, uint32_t offset);

private:

  Datatype& bytes_;
  const uint32_t limit_;
  uint32_t offset_;
};


/*
 * ByteWriter.h implementation
 */

template<typename Datatype>
ByteWriter<Datatype>::ByteWriter(Datatype& bytes, uint32_t limit, uint32_t offset) :
  impl_{std::make_unique<Impl>(bytes, limit, offset)}
{}

// Note: explanation for the syntax
// impl_->template write<...>
//
// https://stackoverflow.com/questions/3786360/confusing-template-error

template<typename Datatype>
ByteWriter<Datatype>& ByteWriter<Datatype>::operator<<(const char& item) {
  impl_->template write<unsigned char>(item);
  return *this;
}

template<typename Datatype>
ByteWriter<Datatype>& ByteWriter<Datatype>::operator<<(const uint32_t& item) {
  impl_->template write<uint32_t>(item);
  return *this;
}

template<typename Datatype>
ByteWriter<Datatype>& ByteWriter<Datatype>::operator<<(const uint64_t& item) {
  impl_->template write<uint64_t>(item);
  return *this;
}

template<typename Datatype>
void ByteWriter<Datatype>::seek(uint32_t offset) {
  impl_->seek(offset);
}

template<typename Datatype>
uint32_t ByteWriter<Datatype>::limit() const {
  return impl_->limit();
}

template<typename Datatype>
uint32_t ByteWriter<Datatype>::offset() const {
  return impl_->offset();
}

template<typename Datatype>
ByteWriter<Datatype>::operator bool() const {
  return (limit() - offset()) > 1;
}


/*
 * Implementations
 */

template<typename Datatype>
ByteWriter<Datatype>::Impl::Impl(Datatype& bytes, uint32_t limit, uint32_t offset) :
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
void ByteWriter<Datatype>::Impl::write(const Numeric& item) {

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

template<typename Datatype>
void ByteWriter<Datatype>::Impl::seek(uint32_t offset) {

  if (offset < limit_) offset_ = offset;
  throw std::out_of_range("Offset value " +
                          std::to_string(offset) +
                          " is not below the limit: " +
                          std::to_string(limit_));
}

template<typename Datatype>
uint32_t ByteWriter<Datatype>::Impl::limit() const {
  return limit_;
}

template<typename Datatype>
uint32_t ByteWriter<Datatype>::Impl::offset() const {
  return offset_;
}