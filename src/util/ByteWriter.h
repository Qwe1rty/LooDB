#ifndef LOODB_BYTEWRITER_H
#define LOODB_BYTEWRITER_H

#include <cstdint>
#include <memory>


class ByteWriter {

public:

  // Writes the byte representations of the second parameter to the
  // location of the byte array specified by the offset.
  //
  // Multi-byte numeric parameters are encoded in little-endian format

  void write(const uint32_t& offset, const char&) const;
  void write(const uint32_t& offset, const uint32_t&) const;
  void write(const uint32_t& offset, const uint64_t&) const;

  ByteWriter(char* const&);
  ByteWriter(const std::unique_ptr<char*>&);
  ByteWriter(const std::unique_ptr<char[]>&);

private:

  class Impl;
  std::unique_ptr<Impl> impl_;
};

#endif //LOODB_BYTEWRITER_H
