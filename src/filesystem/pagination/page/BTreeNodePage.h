#ifndef LOODB_BTREENODEPAGE_H
#define LOODB_BTREENODEPAGE_H

#include "Cell.h"

class BTreeNodePage : public Page {
 
 public:
  uint64_t right_;
  std::vector<Cell> Node_;

  BTreeInternalNode(uint64_t right, std::vector<Cell> node);
  ~ BTreeInternalNode() {}
}

#endif // LOODB_BTREENODEPAGE_H

// more to come
