#ifndef LOODB_BPTREEHEADERPAGE_H
#define LOODB_BPTREEHEADERPAGE_H

#include "Page.h"


class BPTreeHeaderPage : public Page {

  public:

    // tree_root_: has the page number of the root node of our B+ Tree
    uint64_t tree_root_;

    explicit BPTreeHeaderPage(uint64_t root) :
      tree_root_{root}
    {}

  // TODO: more to come
};

#endif
