#include "ByteWriter.h"


/*
 * Constructors
 */

ByteWriter::ByteWriter(char* const& bytes) :
  bytes_{bytes}
{}

ByteWriter::ByteWriter(const std::unique_ptr<char[]>& bytes) :
  bytes_{bytes.get()}
{}

ByteWriter::ByteWriter(const std::unique_ptr<char*>& bytes) :
  bytes_{*bytes}
{}


/*
 * Public methods
 */

void ByteWriter::write(const uint32_t& offset, const uint32_t& item) const {
  for (uint32_t i = 0; i < sizeof(item); ++i) {
    bytes_[offset + i] = (item >> i * 8);
  }
}

void ByteWriter::write(const uint32_t& offset, const uint64_t& item) const {
  for (uint32_t i = 0; i < sizeof(item); ++i) {
    bytes_[offset + i] = (item >> i * 8);
  }
}