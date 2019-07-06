#ifndef LOODB_BTREENODEPAGE_H
#define LOODB_BTREENODEPAGE_H

#include "Cell.h"

class BTreeNodePage : public Page {
// right_: page number of our right node
// Node_: the cells our node (a cell a key, value, pointer trio)
// order: the max number of cells per node 
 public:
  uint64_t right_;
  std::vector<Cell> Node_;
  const static int order = 4;

  BTreeInternalNode(uint64_t right, std::vector<Cell> node);
  ~ BTreeInternalNode() override {}
}

#endif // LOODB_BTREENODEPAGE_H

// more to come
