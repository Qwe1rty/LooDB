#ifndef LOODB_PAGECODEC_H
#define LOODB_PAGECODEC_H

#include "Page.h"

#include <memory>

class PageCodec {

public:

    static std::unique_ptr<char[]> encode(Page);
    static Page decode(std::unique_ptr<char[]>);
};

#endif //LOODB_PAGECODEC_H
