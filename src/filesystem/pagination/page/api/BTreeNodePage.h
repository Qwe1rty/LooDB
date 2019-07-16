#ifndef LOODB_BTREENODEPAGE_H
#define LOODB_BTREENODEPAGE_H

#include "Cell.h"
#include "Page.h"

#include <vector>


class BTreeNodePage : public Page {

  public:

    // ORDER: number of cells per node
    const static uint32_t ORDER;

    // leaf_: whether or not the node is a leaf
    // right_: page number of our right node
    // node_: the cells our node (a cell a key, value, pointer trio)
    bool leaf_;
    uint64_t right_;
    std::vector<Cell> node_;

    BTreeNodePage(bool leaf, uint64_t right, std::vector<Cell> node);
};

#endif // LOODB_BTREENODEPAGE_H