#ifndef LOODB_PAGER_H
#define LOODB_PAGER_H

#include "../../page/api/Page.h"

#include <cstdint>
#include <memory>
#include <string>

class Pager final {

    const static uint64_t DEFAULT_CACHE_LIMIT = 2000;

public:

    explicit Pager(std::string, uint64_t = DEFAULT_CACHE_LIMIT);

    Page read(uint64_t);
    void write(uint64_t, Page);

private:

    class Impl;
    std::unique_ptr<Impl> impl_;
};


#endif //LOODB_PAGER_H
