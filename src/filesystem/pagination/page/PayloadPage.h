#ifndef PAYLOADPAGE_H
#define PAYLOADPAGE_H

class PayloadPage : public Page {

// value_: Row value to be stored; pointed to by cell in B+Tree leaf node
// overflow_: In the case that our values don't fit in one page, we can store the rest in this
//              list of pages 

 public:
  Entry value_;
  uint64_t overflow_;

  PayloadPage(Entry v, uint64_t n, uint64_t o) : value_{v} , next_{n}, overflow_{o} {}
  ~ PayloadPage() override {}
}

#endif
