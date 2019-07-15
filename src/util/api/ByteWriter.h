#ifndef LOODB_BYTEWRITER_H
#define LOODB_BYTEWRITER_H

#include <cstdint>
#include <memory>
#include <limits>


template<typename Datatype>
class ByteWriter {

public:

  /*
   * operator<< writes the byte representations of the integral parameter type to
   * the location of the byte array specified by the internal offset counter
   *
   * The offset counter will automatically be incremented after each write, so
   * sequential writes will be written contiguously
   *
   * Multi-byte numeric parameters are encoded in little-endian format
   */
  ByteWriter& operator<<(const char&);
  ByteWriter& operator<<(const uint32_t&);
  ByteWriter& operator<<(const uint64_t&);

  // Set the offset counter to a desired offset
  void seek(uint32_t);

  // Increment the offset counter
  void skip(uint32_t);

  // Value getters for the writer's current offset, and defined limit
  uint32_t limit() const;
  uint32_t offset() const;

  /*
   * Implicit conversion operator that checks whether the writer can continue writing.
   *
   * If any more bytes are attempted to be written if this returns false, then an
   * out of bounds exception may be thrown. Useful for continuous byte stream writing
   */
  operator bool() const;

  explicit ByteWriter(Datatype&,
                      uint32_t limit = std::numeric_limits<uint32_t>::max(),
                      uint32_t offset = 0);

private:

  class Impl;
  const std::unique_ptr<Impl> impl_;
};


#include "../impl/ByteWriter.cpp"

#endif //LOODB_BYTEWRITER_H
