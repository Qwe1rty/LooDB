#ifndef LOODB_CELL_H
#define LOODB_CELL_H

#include <cstdint>


class Cell {

  public:

    // key_: The page number to the value that is found in one of our columns
    // value_: The primary key page number corresponding to our key
    //		Note: We can't store the primary key's page number yet, we haven't built it
    // left_: page number of the next node to our left
    uint64_t key_;
    uint64_t value_;
    uint64_t left_;

    Cell(uint64_t key, uint64_t value, uint64_t left);
};

#endif


