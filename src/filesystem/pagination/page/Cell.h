#ifndef LOODB_CELL_H
#define LOODB_CELL_H

template <typename Entry>

class Cell {
// key_: A value, integer or string, that is found in one of our columns
// value_: The page number of the primary key corresponding to our key
// left_: page number of the next node to our left
 public:
  Entry key_;
  uint64_t value_;
  uint64_t left_;

//more to come

}

