#ifndef LOODB_PAYLOADOVERFLOWPAGE_H
#define LOODB_PAYLOADOVERFLOWPAGE_H

template<typename Entry>

class PayloadOverflowPage : public Page {
// value_: has the overflowing 
// next_: next page in the overflow list

 public:
  Entry value_;
  uint64_t next_;

  PayloadOverflowPage(Entry v, uint64_t n) : value_{v}, next_{n} {}
  ~ PayloadOverflowPage() override {}
}

#endif
