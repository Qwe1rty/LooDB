#ifndef LOODB_PAYLOADOVERFLOWPAGE_H
#define LOODB_PAYLOADOVERFLOWPAGE_H

#include "Page.h"


template<typename Entry>

class PayloadOverflowPage : public Page {

  public:

    // value_: has the overflowing
    // next_: next page in the overflow list
    Entry value_;
    uint64_t next_;

    PayloadOverflowPage(Entry v, uint64_t n) :
      value_{v},
      next_{n}
    {}
};

#endif
