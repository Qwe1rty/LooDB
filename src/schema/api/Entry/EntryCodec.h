#ifndef LOODB_ENTRYCODEC_H
#define LOODB_ENTRYCODEC_H

#include "Entry.h"
#include "../../../util/api/Codec.h"
#include <memory>

class EntryCodec : public Codec<Entry, std::unique_ptr<char[]>> {
  public:
    std::unique_ptr<char[]> encode(Entry&) const override;
    std::unique_ptr<Entry> decode(std::unique_ptr<char[]>) const override;
};

#endif // LOODB_ENTRYCODEC_H