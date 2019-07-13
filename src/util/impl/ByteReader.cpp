#include "../api/ByteReader.h"


template<typename Datatype>
class ByteReader<Datatype>::Impl {

public:

  uint32_t limit() const;
  uint32_t offset() const;

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
uint32_t ByteReader<Datatype>::Impl::limit() const {
  return limit_;
}

template<typename Datatype>
uint32_t ByteReader<Datatype>::Impl::offset() const {
  return offset_;
}
