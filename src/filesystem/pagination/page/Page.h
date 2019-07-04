#ifndef LOODB_PAGE_H
#define LOODB_PAGE_H

#include <cstdint>

class Page {

    friend class PageCodec;

public:

    const static uint64_t PAGE_SIZE = 4096;

    // TODO: stuff here
};

#endif //LOODB_PAGE_H
