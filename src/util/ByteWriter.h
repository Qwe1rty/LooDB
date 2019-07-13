#ifndef LOODB_BYTEWRITER_H
#define LOODB_BYTEWRITER_H

#include <cstdint>
#include <memory>


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

  explicit ByteWriter(char* const&, uint32_t offset = 0);
  explicit ByteWriter(const std::unique_ptr<char*>&, uint32_t offset = 0);
  explicit ByteWriter(const std::unique_ptr<char[]>&, uint32_t offset = 0);

private:

  class Impl;
  const std::unique_ptr<Impl> impl_;
};

#endif //LOODB_BYTEWRITER_H
