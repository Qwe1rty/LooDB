#ifndef LOODB_BPTREEINTERNALNODEPAGE_H
#define LOODB_BPTREEINTERNALNODEPAGE_H

#include "Cell.h"

class BPTreeInternalNodePage : public Page {

 public:
  uint64_t right_;
  std::vector<Cell> Node_;

  BPTreeInternalNode(uint64_t right, std::vector<Cell> node);
  ~ BPTreeInternalNode() {}
}

#endif

// more to come
