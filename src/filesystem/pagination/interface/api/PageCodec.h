#ifndef LOODB_PAGECODEC_H
#define LOODB_PAGECODEC_H

#include "../../../../util/Codec.h"
#include <memory>

class Page;

template<typename Object, typename Serial>
class Codec;

class PageCodec : public Codec<Page, std::unique_ptr<char[]>> {
  public:
    std::unique_ptr<char[]> encode(Page&) const override;
    std::unique_ptr<Page> decode(std::unique_ptr<char[]>) const override;
};

#endif //LOODB_PAGECODEC_H