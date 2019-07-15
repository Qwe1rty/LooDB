#ifndef LOODB_PAGECODEC_H
#define LOODB_PAGECODEC_H

#include "../../../../util/api/Codec.h"
#include "../../page/api/Page.h"

#include <array>
#include <memory>


class PageCodec : public Codec<std::unique_ptr<Page>,
                               std::array<char, Page::SIZE>> {

  public:

    // CODEC: Converter interface (similar to singleton)
    const static PageCodec CODEC;

    using Object = std::unique_ptr<Page>;
    using Serial = std::array<char, Page::SIZE>;

    Serial encode(const Object&) const override;
    Object decode(const Serial&) const override;
};

#endif //LOODB_PAGECODEC_H