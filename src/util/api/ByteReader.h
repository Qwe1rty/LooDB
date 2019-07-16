#ifndef LOODB_BYTEREADER_H
#define LOODB_BYTEREADER_H

#include <memory>
#include <limits>


template<typename Datatype>
class ByteReader {

public:

  ByteReader& operator>>(char&);
  ByteReader& operator>>(bool&);
  ByteReader& operator>>(uint32_t&);
  ByteReader& operator>>(uint64_t&);

  // Value getters for the reader's current offset, and defined limit
  uint32_t limit() const;
  uint32_t offset() const;

  // Increment the offset counter
  void skip(uint32_t);

  explicit ByteReader(const Datatype&,
                      uint32_t limit = std::numeric_limits<uint32_t>::max(),
                      uint32_t offset = 0);

private:

  class Impl;
  const std::unique_ptr<Impl> impl_;
};


#include "../impl/ByteReader.tpp"

#endif //LOODB_BYTEREADER_H
