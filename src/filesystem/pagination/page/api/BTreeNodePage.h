#ifndef LOODB_BTREENODEPAGE_H
#define LOODB_BTREENODEPAGE_H

#include "Cell.h"
#include "Page.h"

#include <vector>


class BTreeNodePage : public Page {

  public:

    // right_: page number of our right node
    // node_: the cells our node (a cell a key, value, pointer trio)
    // order: the max number of cells per node
    uint64_t right_;
    std::vector<Cell> node_;
    const static int order = 4;

    BTreeNodePage(uint64_t right, std::vector<Cell> node) :
      right_{right},
      node_{std::move(node)}
    {}

  // TODO: more to come
};

#endif // LOODB_BTREENODEPAGE_H