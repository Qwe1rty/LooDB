#ifndef LOODB_CELL_H
#define LOODB_CELL_H

#include "../../../../schema/Entry.h"

#include <cstdint>


class Cell {

  public:

    // key_: A value, integer or string, that is found in one of our columns
    // value_: The primary key page number corresponding to our key
    //		Note: We can't store the primary key's page number yet, we haven't built it
    // left_: page number of the next node to our left
    Entry key_;
    Entry value_;
    uint64_t left_;

    Cell(Entry k, Entry v, uint64_t l) :
      key_{k},
      value_{v},
      left_{l}
    {}

  // TODO: more to come
};

#endif


