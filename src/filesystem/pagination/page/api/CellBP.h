#ifndef LOODB_CELLBP_H
#define LOODB_CELLBP_H

#include "../../../../schema/Entry.h"

#include <cstdint>
#include <vector>


class CellBP {

  public:

    // key_: A value, integer or string, representing a primary key
    // values_: The page numbers of the items stored in the row corresponding to our key
    Entry key_;
    std::vector<uint64_t> values_;

    CellBP(Entry k, std::vector<uint64_t> v) :
      key_{k},
      values_{std::move(v)}
    {}

  // TODO: more to come
};

#endif
