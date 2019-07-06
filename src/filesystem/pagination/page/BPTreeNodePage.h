#ifndef LOODB_BPTREENODEPAGE_H
#define LOODB_BPTREENODEPAGE_H

#include "CellBP.h"

class BPTreeNodePage : public Page {
// right_: This is the page number of the leaf node to our right
// node_: The list of leaf cells in our node

 public:
  uint64_t right_;
  std::vector<CellBP> node_;
  const static int order = 5;

  BPTreeNode(uint64_t right, std::vector<CellBP> node_);
  ~ BPTreeNode() {}
}

#endif

// more to come
