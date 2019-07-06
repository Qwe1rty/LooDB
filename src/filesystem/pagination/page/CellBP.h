#ifndef LOODB_CELLBP_H
#define LOODB_CELLBP_H

template <typename Entry>

class CellBP {
// key_: A value, integer or string, representing a primary key
// value_: The page number of the items stored in the row corresponding to our key
// overflow_: In the case that our values don't fit in one page, we can store the rest in this
//              list of pages

 public:
  Entry key_;
  uint64_t value_;
  uint64_t overflow_;

//more to come

}

#endif
