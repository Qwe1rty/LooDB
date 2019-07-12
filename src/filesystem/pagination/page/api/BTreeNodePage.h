#ifndef LOODB_BTREENODEPAGE_H
#define LOODB_BTREENODEPAGE_H

#include "Cell.h"
#include "Page.h"

#include <vector>


class BTreeNodePage : public Page {

  public:

    const static int ORDER = 4;

    // right_: page number of our right node
    // node_: the cells our node (a cell a key, value, pointer trio)
    // order: the max number of cells per node
    uint64_t right_;
    std::vector<Cell> node_;

    BTreeNodePage(uint64_t right, std::vector<Cell> node);
};

#endif // LOODB_BTREENODEPAGE_H