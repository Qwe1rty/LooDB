#ifndef LOODB_BPTREEHEADERPAGE_H
#define LOODB_BPTREEHEADERPAGE_H

#include "Page.h"


class BPTreeHeaderPage : public Page {

  public:

    // root_: has the page number of the root node of our B+ Tree
    uint64_t root_;

    explicit BPTreeHeaderPage(uint64_t);
};

#endif
