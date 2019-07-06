#ifndef LOODB_DATABASEHEADERPAGE_H
#define LOODB_DATABASEHEADERPAGE_H

#include "Page.h"

#include <vector>


class DatabaseHeaderPage : public Page {

  public:

    // columns_: stores the page numbers of header pages belonging to BTrees (columns)
    // bp_header_: has the page number of our B+Tree's header page
    std::vector<uint64_t> columns_;
    uint64_t bp_header_;

    DatabaseHeaderPage(std::vector<uint64_t> c, uint64_t bp) :
      columns_{std::move(c)},
      bp_header_{bp}
    {}
};

#endif
