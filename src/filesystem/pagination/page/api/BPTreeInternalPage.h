#ifndef LOODB_BPTREEINTERNALPAGE_H
#define LOODB_BPTREEINTERNALPAGE_H

#include "Cell.h"
#include "Page.h"

#include <vector>


class BPTreeInternalPage : public Page {

  public:

    // ORDER: the number of children a node has
    const static uint32_t ORDER;

    // right_: The page number of our child to the right of node
    // node_: A list of cells in our node, each node with order 4 (4 cells each)
    uint64_t right_;
    std::vector<Cell> node_;

    BPTreeInternalPage(uint64_t, std::vector<Cell>);
};

#endif