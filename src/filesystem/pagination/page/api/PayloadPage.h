#ifndef PAYLOADPAGE_H
#define PAYLOADPAGE_H

#include "Page.h"
#include "../../../../schema/Entry.h"


class PayloadPage : public Page {

  public:

    // value_: Row value to be stored; pointed to by cell in B+Tree leaf node
    // overflow_: In the case that our values don't fit in one page, we can store the rest in this
    //            list of pages
    Entry value_;
    uint64_t next_;
    uint64_t overflow_;

    PayloadPage(Entry value, uint64_t next, uint64_t overflow) :
      value_{value},
      next_{next},
      overflow_{overflow}
    {}
};

#endif
