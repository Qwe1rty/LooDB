#ifndef LOODB_BPTREELEAFPAGE_H
#define LOODB_BPTREELEAFPAGE_H

#include "CellBP.h"
#include "Page.h"

#include <vector>


class BPTreeLeafPage : public Page {

 public:

    // ORDER: number of cells per node
    const static uint32_t ORDER;

    // right_: This is the page number of the leaf node to our right
    // node_: The list of leaf cells in our node
    uint64_t right_;
    std::vector<CellBP> node_;

    BPTreeLeafPage(uint64_t, std::vector<CellBP>);
};

#endif