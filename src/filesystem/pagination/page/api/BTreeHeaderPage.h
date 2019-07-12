#ifndef LOODB_BTREEHEADERPAGE_H
#define LOODB_BTREEHEADERPAGE_H

#include "Page.h"


class BTreeHeaderPage : public Page {

  public:

    // root_: Has the page number of the root node in our BTree
    uint64_t root_;

    explicit BTreeHeaderPage(uint64_t);
};

#endif
