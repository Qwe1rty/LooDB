#ifndef LOODB_BPTREEINTERNALNODEPAGE_H
#define LOODB_BPTREEINTERNALNODEPAGE_H

#include "Cell.h"
#include "Page.h"

#include <vector>


class BPTreeInternalNodePage : public Page {

  public:

    // ORDER: the number of children a node has
    const static uint32_t ORDER = 4;

    // right_: The page number of our child to the right of node
    // Node_: A list of cells in our node, each node with order 4 (4 cells each)
    uint64_t right_;
    std::vector<Cell> node_;

    BPTreeInternalNodePage(uint64_t right, std::vector<Cell> node) :
      right_{right},
      node_{std::move(node)}
    {}

  // TODO: more to come
};

#endif