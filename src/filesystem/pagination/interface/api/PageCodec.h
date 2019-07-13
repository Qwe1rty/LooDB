#ifndef LOODB_PAGECODEC_H
#define LOODB_PAGECODEC_H

#include "../../../../util/Codec.h"
#include "../../page/api/Page.h"

#include <memory>


class Page;

template<typename Object, typename Serial>
class Codec;

class PageCodec : public Codec<std::unique_ptr<Page>,
                               std::unique_ptr<char[]>> {
  public:

    using Object = std::unique_ptr<Page>;
    using Serial = std::unique_ptr<char[]>;

    Serial encode(const Object&) const override;
    Object decode(const Serial&) const override;
};

#endif //LOODB_PAGECODEC_H