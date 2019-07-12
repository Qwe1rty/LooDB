#ifndef PAYLOADPAGE_H
#define PAYLOADPAGE_H

#include  "Page.h"


class EntryPage : public Page {

  public:

    // value_: Row value to be stored; pointed to by cell in B+Tree leaf node
    // overflow_: In the case that our values don't fit in one page, we can store the rest in this
    //            list of pages. Will be 0 if no overflow
    std::unique_ptr<char[]> value_;
    uint64_t overflow_;

    EntryPage(std::unique_ptr<char[]> value, uint64_t overflow);
};

#endif
