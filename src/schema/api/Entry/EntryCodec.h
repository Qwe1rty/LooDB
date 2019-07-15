#ifndef LOODB_ENTRYCODEC_H
#define LOODB_ENTRYCODEC_H

#include "Entry.h"
#include "../../../util/api/Codec.h"
#include <memory>
#include <vector>

class EntryCodec : public Codec<std::unique_ptr<Entry>, std::vector<char>> {
  public:

    using Object = std::unique_ptr<Entry>;
    using Serial = std::vector<char>;

    Serial encode(const Object&) const override;
    Object decode(const Serial&) const override;
};

#endif // LOODB_ENTRYCODEC_H