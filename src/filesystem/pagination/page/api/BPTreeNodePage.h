#ifndef LOODB_BPTREENODEPAGE_H
#define LOODB_BPTREENODEPAGE_H

#include "CellBP.h"
#include "Page.h"

#include <vector>


class BPTreeNodePage : public Page {

 public:

    // ORDER: number of cells per node
    const static uint32_t ORDER = 4;

    // right_: This is the page number of the leaf node to our right
    // node_: The list of leaf cells in our node
    uint64_t right_;
    std::vector<CellBP> node_;


    BPTreeNodePage(uint64_t right, std::vector<CellBP> node) :
      right_{right},
      node_{std::move(node)}
    {}

  // TODO: more to come
};

#endif

// more to come
