#ifndef LOODB_PAYLOADPAGE_H
#define LOODB_PAYLOADPAGE_H

#include  "Page.h"

#include <vector>


class EntryPage : public Page {

  public:

    // CAPACITY: The maximum amount of bytes that can be stored
    const static uint32_t CAPACITY;

    // value_: Row value to be stored; pointed to by cell in B+Tree leaf node
    // overflow_: In the case that our values don't fit in one page, we can store the rest in this
    //            list of pages. Will be 0 if no overflow
    std::vector<char> value_;
    uint64_t overflow_;

    EntryPage(std::vector<char> value, uint64_t overflow);
};

#endif
