#ifndef LOODB_BPTREEINTERNALNODEPAGE_H
#define LOODB_BPTREEINTERNALNODEPAGE_H

#include "Cell.h"

class BPTreeInternalNodePage : public Page {
// right_: The page number of our child to the right of node
// Node_: A list of cells in our node, each node with order 4 (4 cells each)
 
 public:
  const static int order = 4;
  uint64_t right_;
  std::vector<Cell> Node_;

  BPTreeInternalNode(uint64_t right, std::vector<Cell> node);
  ~ BPTreeInternalNode() override {}
}

#endif

// more to come
